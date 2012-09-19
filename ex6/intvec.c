#include "intvec.h"

#include <stdlib.h>
#include <err.h>


#define START_CAPACITY 4


IntVec * intvec_new ()
{
  IntVec * vec;
  if (NULL == (vec = calloc (1, sizeof (*vec))))
    err (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  return vec;
}


void intvec_delete (IntVec * vec)
{
  free (vec->arr);
  free (vec);
}


static void grow (IntVec * vec)
{
  size_t newcap;
  int * newarr;
  
  if (0 == vec->cap) {
    if (NULL == (vec->arr = malloc (START_CAPACITY * sizeof(*vec->arr))))
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    vec->cap = START_CAPACITY;
  }
  else {
    newcap = 2 * vec->cap;
    if (NULL == (newarr = realloc (vec->arr, newcap * sizeof(*vec->arr))))
      err (EXIT_FAILURE, __FILE__": %s: realloc", __func__);
    vec->arr = newarr;
    vec->cap = newcap;
  }
}


void intvec_ins (IntVec * vec, size_t pos, int value)
{
  if (pos > vec->len)
    pos = vec->len;
  
  if (vec->len >= vec->cap)
    grow (vec);
  
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


int intvec_rem (IntVec * vec, size_t pos)
{
  int result;
  int *dst;
  
  if (0 == vec->len)
    errx (EXIT_FAILURE, __FILE__": %s: empty vector (violated precondition)", __func__);
  
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


size_t intvec_ins_asc (IntVec * vec, int num)
{
  size_t pos;
  for (pos = 0; pos < vec->len; ++pos)
    if (vec->arr[pos] > num)
      break;
  intvec_ins (vec, pos, num);
  return pos;
}


size_t intvec_ins_desc (IntVec * vec, int num)
{
  size_t pos;
  for (pos = 0; pos < vec->len; ++pos)
    if (vec->arr[pos] < num)
      break;
  intvec_ins (vec, pos, num);
  return pos;
}


int intvec_linsearch (IntVec * vec, int num, size_t * pos)
{
  size_t ii;
  for (ii = 0; ii < vec->len; ++ii)
    if (vec->arr[ii] == num) {
      *pos = ii;
      return 1;
    }
  return 0;
}


int intvec_findmin (IntVec * vec, size_t * pos)
{
  int min_so_far;
  size_t ii;
  if (0 == vec->len)
    return 0;
  min_so_far = vec->arr[0];
  *pos = 0;
  for (ii = 1; ii < vec->len; ++ii)
    if (vec->arr[ii] < min_so_far) {
      min_so_far = vec->arr[ii];
      *pos = ii;
    }
  return 1;
}


int intvec_findmax (IntVec * vec, size_t * pos)
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


int intvec_binsearch (IntVec * vec, int num, size_t * pos)
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


void intvec_dump (IntVec * vec, char * name, FILE * of)
{
  size_t ii;
  fprintf (of, "%s [%2lu/%2lu]", name, vec->len, vec->cap);
  for (ii = 0; ii < vec->len; ++ii)
    fprintf (of, " %3d", vec->arr[ii]);
  fprintf (of, "\n");
}
