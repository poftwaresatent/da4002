#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_CAPACITY 4


/*
 * The vector_s encapsulates all the data required to manage the
 * dynamic array storage on which the vector is built.
 */
typedef struct vector_s {
  int * arr;			/* array of values (pointer to first element) */
  unsigned long len;		/* length of vector (number of actually stored values) */
  unsigned long cap;		/* current capacity (max length) */
} Vector;


/*
 * Initialization function, needs to be called once for each vector
 * instance, before it can be used.
 */
void vector_init (Vector * vec)
{
  vec->arr = NULL;
  vec->len = 0;
  vec->cap = 0;
}


/*
 * Cleanup function, has to be called after you're done with a vector
 * to give all used memory back to the operating system.
 */
void vector_destroy (Vector * vec)
{
  free (vec->arr);
  vec->arr = NULL;
  vec->len = 0;
  vec->cap = 0;
}


/*
 * Utility function to grow the capacity: it simply get doubled each
 * time you calll vector_grow. This function is called by the more
 * "user visible" functions like vector_append.
 *
 * \return zero on success.
 */
int vector_grow (Vector * vec)
{
  unsigned long newcap;
  int * newarr;
  
  if (0 == vec->cap) {
    
    vec->arr = malloc (START_CAPACITY * sizeof(*vec->arr));
    if (NULL == vec->arr)
      return -1;
    
    vec->cap = START_CAPACITY;
    
    return 0;
  }
  
  newcap = 2 * vec->cap;
  
  newarr = malloc (newcap * sizeof(*vec->arr));
  if (NULL == newarr)
    return -1;
  
  memcpy (newarr, vec->arr, vec->len * sizeof(*vec->arr));
  free (vec->arr);
  vec->arr = newarr;
  vec->cap = newcap;
  
  return 0;
}


/*
 * User function to append a value to the vector. It grows the
 * underlying array if necessary, using the vector_grow utility
 * function.
 *
 * \return zero on success.
 */
int vector_append (Vector * vec, int value)
{
  if (vec->len >= vec->cap) {
    if (0 != vector_grow (vec))
      return -1;
  }
  vec->arr[vec->len++] = value;
  return 0;
}


void vector_dump (Vector * vec)
{
  unsigned long ii;
  printf ("[%2lu/%2lu]", vec->len, vec->cap);
  for (ii = 0; ii < vec->len; ++ii)
    printf (" %3d", vec->arr[ii]);
  for (/* keep ii */; ii < vec->cap; ++ii)
    printf (" xxx");
  printf ("\n");
}


/*
 * User function to prepend a value to the beginning of a vector. In
 * other words, after prepending the value, vec->arr[0] will be that
 * value, and the previous contents will have been shifted one
 * position towards the end of the vector.
 *
 * \return zero on success.
 */
int vector_prepend (Vector * vec, int value)
{
  if (vec->len >= vec->cap) {
    if (0 != vector_grow (vec))
      return -1;
  }
  
  if (0 < vec->len) {
    int *dst = vec->arr + vec->len;
    int *src = dst - 1;
    while (dst != vec->arr)
      *(dst--) = *(src--);
  }
  
  vec->arr[0] = value;
  ++vec->len;
  
  return 0;
}


/*
 * User function to insert a value at a specified position into a
 * vector. In other words, after inserting the value at pos,
 * vec->arr[pos] will be that value, everything before pos will be
 * untouched, and everything after pos will have been shifted one
 * position towards the end of the vector.
 *
 * \return zero on success.
 */
int vector_insert (Vector * vec, unsigned long pos, int value)
{
  int *dst, *src, *stp;
  
  if (pos > vec->len)
    return -2;
  if (pos == vec->len)
    return vector_append (vec, value);
  if (pos == 0)
    return vector_prepend (vec, value);
  
  if (vec->len >= vec->cap) {
    if (0 != vector_grow (vec))
      return -1;
  }
  
  dst = vec->arr + vec->len;
  src = dst - 1;
  stp = vec->arr + pos;
  while (dst != stp)
    *(dst--) = *(src--);
  
  vec->arr[pos] = value;
  ++vec->len;
  
  return 0;
}


/*
 * User function to remove an entry from the vector. In other words,
 * after removing the entry at pos, vec->arr[pos] will either be
 * invalid (if pos was the last entry) or it will be whatever used to
 * be at pos+1. All the values after the removed one will have been
 * moveed one step towards the beginning of the vector.
 *
 * \note This function does not shrink the capacity (that would be a
 * nice feature, but don't worry about that now).
 *
 * \return zero on success.
 */
int vector_remove (Vector * vec, unsigned long pos)
{
  int *dst, *src, *stp;
  
  if (pos >= vec->len)
    return -1;
  
  --(vec->len);
  dst = vec->arr + pos;
  src = dst + 1;
  stp = vec->arr + vec->len;
  while (dst != stp)
    *(dst++) = *(src++);
  
  return 0;
}


/*
 * Unit test for the vector_append function. Runs some example
 * operations and checks that results are as expected, writing
 * messages to the terminal so that errors can be detected and
 * pinpointed.
 *
 * \return zero on success.
 */
int test_append (void)
{
  Vector vec;
  int ii;
  
  printf ("\nrunning test_append...\n");
  
  vector_init (&vec);
  printf ("initialized: ");
  vector_dump (&vec);
  
  for (ii = -3; ii < 10; ++ii) {
    if (0 != vector_append (&vec, ii)) {
      printf ("test_append ERROR: could not append %d\n", ii);
      vector_destroy (&vec);
      return -1;
    }
    printf ("appended %2d: ", ii);
    vector_dump (&vec);
  }
  
  for (ii = -3; ii < 10; ++ii)
    if (vec.arr[ii+3] != ii) {
      printf ("test_append ERROR: arr[%d] should be %d but is %d\n", ii+3, ii, vec.arr[ii+3]);
      vector_destroy (&vec);
      return -1;
    }
  
  printf ("test_append SUCCESS\n");
  
  vector_destroy (&vec);
  return 0;
}


/*
 * Unit test for the vector_prepend function. Runs some example
 * operations and checks that results are as expected, writing
 * messages to the terminal so that errors can be detected and
 * pinpointed.
 *
 * \return zero on success.
 */
int test_prepend (void)
{
  Vector vec;
  int ii;
  
  printf ("\nrunning test_prepend...\n");
  
  vector_init (&vec);
  printf ("initialized: ");
  vector_dump (&vec);
  
  for (ii = -3; ii < 10; ++ii) {
    if (0 != vector_prepend (&vec, ii)) {
      printf ("test_prepend ERROR: could not prepend %d\n", ii);
      vector_destroy (&vec);
      return -1;
    }
    printf ("prepended %2d: ", ii);
    vector_dump (&vec);
  }
  
  for (ii = 0; ii < 13; ++ii)
    if (vec.arr[ii] != 9-ii) {
      printf ("test_prepend ERROR: arr[%d] should be %d but is %d\n", ii, 9-ii, vec.arr[ii]);
      vector_destroy (&vec);
      return -1;
    }
  
  printf ("test_prepend SUCCESS\n");
  
  vector_destroy (&vec);
  return 0;
}


/*
 * Unit test for the vector_insert function. Runs some example
 * operations and checks that results are as expected, writing
 * messages to the terminal so that errors can be detected and
 * pinpointed.
 *
 * \return zero on success.
 */
int test_insert (void)
{
  static int const check[] = {
    102, 101, 209, 208, 207, 206, 205, 204, 203, 100, 99, 98, 97
  };
  static unsigned long const checklen = sizeof(check) / sizeof(*check);
  
  Vector vec;
  int ii;
  
  printf ("\nrunning test_insert...\n");
  
  vector_init (&vec);
  printf ("initialized: ");
  vector_dump (&vec);
  
  if (0 == vector_insert(&vec, 11, 42)) {
    printf ("test_insert ERROR: should not have been able to insert at invalid index\n");
    vector_destroy (&vec);
    return -1;
  }
  
  for (ii = -3; ii < 3; ++ii) {
    if (0 != vector_insert (&vec, 0, 100+ii)) {
      printf ("test_insert ERROR: could not insert %d at pos 0\n", 100+ii);
      vector_destroy (&vec);
      return -1;
    }
    printf ("inserted %3d at pos 0: ", 100+ii);
    vector_dump (&vec);
  }
  
  for (; ii < 10; ++ii) {
    if (0 != vector_insert (&vec, 2, 200+ii)) {
      printf ("test_insert ERROR: could not insert %d at pos 2\n", 200+ii);
      vector_destroy (&vec);
      return -1;
    }
    printf ("inserted %3d at pos 2: ", 200+ii);
    vector_dump (&vec);
  }
  
  if (checklen != vec.len) {
    printf ("test_insert ERROR: vector length should be %lu but is %lu\n", checklen, vec.len);
    vector_destroy (&vec);
    return -2;
  }
  
  for (ii = 0; ii < checklen; ++ii)
    if (vec.arr[ii] != check[ii]) {
      printf ("test_insert ERROR: arr[%d] should be %d but is %d\n", ii, check[ii], vec.arr[ii]);
      vector_destroy (&vec);
      return -1;
    }
  
  printf ("test_insert SUCCESS\n");
  
  vector_destroy (&vec);
  return 0;
}


/*
 * Unit test for the vector_remove function. Runs some example
 * operations and checks that results are as expected, writing
 * messages to the terminal so that errors can be detected and
 * pinpointed.
 *
 * \return zero on success.
 */
int test_remove (void)
{
  static unsigned long const remlist[] = { 9, 0, 4, 4 };
  static unsigned long const remlistlen = sizeof(remlist) / sizeof(*remlist);
  
  static int const check[] = { 101, 102, 103, 104, 107, 108 };
  static unsigned long const checklen = sizeof(check) / sizeof(*check);
  
  Vector vec;
  int ii;
  
  printf ("\nrunning test_remove...\n");
  
  vector_init (&vec);
  printf ("initialized: ");
  vector_dump (&vec);
  
  if (0 == vector_remove(&vec, 11)) {
    printf ("test_remove ERROR: should not have been able to remove at invalid index\n");
    vector_destroy (&vec);
    return -1;
  }
  
  for (ii = 0; ii < 10; ++ii) {
    if (0 != vector_append (&vec, 100+ii)) {
      printf ("test_remove ERROR: could not append %d\n", 100+ii);
      vector_destroy (&vec);
      return -1;
    }
    printf ("appended %2d: ", 100+ii);
    vector_dump (&vec);
  }
  
  for (ii = 0; ii < remlistlen; ++ii) {
    if (0 != vector_remove (&vec, remlist[ii])) {
      printf ("test_remove ERROR: could not remove pos %lu\n", remlist[ii]);
      vector_destroy (&vec);
      return -1;
    }
    printf ("removed pos %lu: ", remlist[ii]);
    vector_dump (&vec);
  }
  
  if (0 == vector_remove(&vec, vec.len)) {
    printf ("test_remove ERROR: should not have been able to remove beyond end\n");
    vector_destroy (&vec);
    return -1;
  }
  
  if (checklen != vec.len) {
    printf ("test_remove ERROR: vector length should be %lu but is %lu\n", checklen, vec.len);
    vector_destroy (&vec);
    return -2;
  }
  
  for (ii = 0; ii < checklen; ++ii)
    if (vec.arr[ii] != check[ii]) {
      printf ("test_remove ERROR: arr[%d] should be %d but is %d\n", ii, check[ii], vec.arr[ii]);
      vector_destroy (&vec);
      return -1;
    }
  
  printf ("test_remove SUCCESS\n");
  
  vector_destroy (&vec);
  return 0;
}


/*
 * The main function just calls all unit tests and prints a summary
 * message (success or failure).
 *
 * \return zero on success.
 */
int main (int argc, char ** argv)
{
  int ok = 1;
  if (0 != test_append())
    ok = 0;
  if (0 != test_prepend())
    ok = 0;
  if (0 != test_insert())
    ok = 0;
  if (0 != test_remove())
    ok = 0;
  
  if (ok) {
    printf ("\nall tests PASSED\n");
    return 0;
  }
  printf ("\none or more tests FAILED\n");
  return 1;
}
