#include <stdio.h>
#include <stdlib.h>
#include <err.h>


#define START_CAPACITY 4


typedef struct vector_s {
  int * arr;
  size_t len;
  size_t cap;
} Vector;


Vector * vector_new ()
{
  Vector * vec;
  if (NULL == (vec = calloc (1, sizeof (*vec))))
    err (EXIT_FAILURE, "vector_new: calloc");
  return vec;
}


void vector_delete (Vector * vec)
{
  free (vec->arr);
  free (vec);
}


void vector_grow (Vector * vec)
{
  size_t newcap;
  int * newarr;
  
  if (0 == vec->cap) {
    if (NULL == (vec->arr = malloc (START_CAPACITY * sizeof(*vec->arr))))
      err (EXIT_FAILURE, "vector_grow: malloc");
    vec->cap = START_CAPACITY;
  }
  else {
    newcap = 2 * vec->cap;
    if (NULL == (newarr = realloc (vec->arr, newcap * sizeof(*vec->arr))))
      err (EXIT_FAILURE, "vector_grow: realloc");
    vec->arr = newarr;
    vec->cap = newcap;
  }
}


void vector_ins (Vector * vec, size_t pos, int value)
{
  if (pos > vec->len)
    pos = vec->len;
  
  if (vec->len >= vec->cap)
    vector_grow (vec);
  
  if (pos < vec->len) {
    int *dst, *src, *stp;
    dst = vec->arr + vec->len;
    src = dst - 1;
    stp = vec->arr + pos;
    while (dst != stp)
      *(dst--) = *(src--);
  }
  
  vec->arr[pos] = value;
  ++vec->len;
}


int vector_rem (Vector * vec, size_t pos)
{
  int result;
  int *dst;
  
  if (0 == vec->len)
    errx (EXIT_FAILURE, "vector_rem: empty vector");
  
  if (pos >= vec->len)
    pos = vec->len - 1;
  
  --(vec->len);
  dst = vec->arr + pos;
  result = *dst;
  
  if (pos != vec->len) {
    int *src, *stp;
    src = dst + 1;
    stp = vec->arr + vec->len;
    while (dst != stp)
      *(dst++) = *(src++);
  }
  
  return result;
}


size_t vector_ins_sorted (Vector * vec, int num)
{
  size_t pos;
  for (pos = 0; pos < vec->len; ++pos)
    if (vec->arr[pos] < num)
      break;
  vector_ins (vec, pos, num);
  return pos;
}


int vector_linsearch (Vector * vec, int num, size_t * pos)
{
  size_t ii;
  for (ii = 0; ii < vec->len; ++ii)
    if (vec->arr[ii] == num) {
      *pos = ii;
      return 1;
    }
  return 0;
}


int vector_findmax (Vector * vec, size_t * pos)
{
  int max_so_far;
  size_t ii;
  if (0 == vec->len)
    return 0;
  max_so_far = vec->arr[0];
  *pos = 0;
  for (ii = 1; ii < vec->len; ++ii)
    if (vec->arr[ii] > max_so_far) {
      max_so_far = vec->arr[ii];
      *pos = ii;
    }
  return 1;
}


int vector_binsearch (Vector * vec, int num, size_t * pos)
{
  size_t low = 0;
  size_t high = vec->len - 1;
  while (low <= high) {
    size_t mid = (low + high) / 2;
    if (vec->arr[mid] < num)
      low = mid + 1;
    else if (vec->arr[mid] > num)
      high = mid - 1;
    else {
      *pos = mid;
      return 1;
    }
  }
  return 0;
}


void vector_dump (Vector * vec, char * name)
{
  size_t ii;
  printf ("%s [%2lu/%2lu]", name, vec->len, vec->cap);
  for (ii = 0; ii < vec->len; ++ii)
    printf (" %3d", vec->arr[ii]);
  printf ("\n");
}


void pq1_insert (Vector * vec, int num)
{
  vector_ins (vec, vec->len, num);
}


int pq1_extract (Vector * vec)
{
  size_t pos;
  if ( ! vector_findmax (vec, &pos))
    errx (EXIT_FAILURE, "pq1_extract: vector_findmax failed (empty vector?)");
  return vector_rem (vec, pos);
}


void pq2_insert (Vector * vec, int num)
{
  vector_ins_sorted (vec, num);
}


int pq2_extract (Vector * vec)
{
  return vector_rem (vec, 0);
}


int main (int argc, char ** argv)
{
  int ii;
  Vector *pq1, *pq2;
  pq1 = vector_new ();
  pq2 = vector_new ();
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, "failed to parse integer from argument %d `%s'", ii, argv[ii]);
    pq1_insert (pq1, num);
    pq2_insert (pq2, num);
    printf ("inserted %d\n", num);
    vector_dump (pq1, "  pq1");
    vector_dump (pq2, "  pq2");
  }
  
  printf ("--------------------------------------------------\n");
  while (0 < pq1->len && 0 < pq2->len) {
    int n1 = pq1_extract (pq1);
    int n2 = pq2_extract (pq2);
    if (n1 != n2)
      errx (EXIT_FAILURE, "oops, the queues don't agree (%d != %d)", n1, n2);
    fprintf (stderr, "extracted %d\n", n1);
    vector_dump (pq1, "  pq1");
    vector_dump (pq2, "  pq2");
  }
  
  if (pq1->len != pq2->len)
    errx (EXIT_FAILURE, "oops, one of the queues is not empty...");
  
  vector_delete (pq1);
  vector_delete (pq2);
  
  return 0;
}
