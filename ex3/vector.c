#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_CAPACITY 4


typedef struct vector_s {
  int * arr;
  unsigned long len, cap;
} Vector;


void vector_init (Vector * vec)
{
  vec->arr = NULL;
  vec->len = 0;
  vec->cap = 0;
}


void vector_destroy (Vector * vec)
{
  free (vec->arr);
  vec->arr = NULL;
  vec->len = 0;
  vec->cap = 0;
}


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
    printf (" %2d", vec->arr[ii]);
  for (/* keep ii */; ii < vec->cap; ++ii)
    printf (" xx");
  printf ("\n");
}


/* fill in */
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
      return -1;
    }
    printf ("appended %2d: ", ii);
    vector_dump (&vec);
  }
  
  for (ii = -3; ii < 10; ++ii)
    if (vec.arr[ii+3] != ii) {
      printf ("test_append ERROR: arr[%d] should be %d but is %d\n", ii+3, ii, vec.arr[ii+3]);
      return -1;
    }
  
  printf ("test_append SUCCESS\n");
  
  return 0;
}


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
      return -1;
    }
    printf ("prepended %2d: ", ii);
    vector_dump (&vec);
  }
  
  for (ii = 0; ii < 13; ++ii)
    if (vec.arr[ii] != 9-ii) {
      printf ("test_prepend ERROR: arr[%d] should be %d but is %d\n", ii, 9-ii, vec.arr[ii]);
      return -1;
    }
  
  printf ("test_prepend SUCCESS\n");
  
  return 0;
}


int test_insert (void)
{
  Vector vec;
  int ii;
  
  printf ("\nrunning test_insert...\n");
  
  vector_init (&vec);
  printf ("initialized: ");
  vector_dump (&vec);
  
  if (0 == vector_insert(&vec, 11, 42)) {
    printf ("test_insert ERROR: should not have been able to insert at invalid index\n");
    return -1;
  }
  
  for (ii = -3; ii < 10; ++ii) {
    if (0 != vector_insert (&vec, ii)) {
      printf ("test_insert ERROR: could not insert %d\n", ii);
      return -1;
    }
    printf ("inserted %2d: ", ii);
    vector_dump (&vec);
  }
  
  for (ii = 0; ii < 13; ++ii)
    if (vec.arr[ii] != 9-ii) {
      printf ("test_insert ERROR: arr[%d] should be %d but is %d\n", ii, 9-ii, vec.arr[ii]);
      return -1;
    }
  
  printf ("test_insert SUCCESS\n");
  
  return 0;
}



int main (int argc, char ** argv)
{
  int ok = 1;
  if (0 != test_append())
    ok = 0;
  if (0 != test_prepend())
    ok = 0;
  if (0 != test_insert())
    ok = 0;
  
  if (ok) {
    printf ("\nall tests PASSED\n");
    return 0;
  }
  printf ("\none or more tests FAILED\n");
  return 1;
}
