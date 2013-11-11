#include "test-sorting-algo.h"

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/uio.h>
#include <sys/time.h>


/***************************************************
  Merge sort implementation
***************************************************/


static void merge (int * arr, int * tmp, size_t beg, size_t mid, size_t end)
{
  size_t ii = beg;
  size_t jj = mid;
  size_t kk = beg;
  
  while (ii < mid && jj < end) {
    if (arr[ii] < arr[jj]) {
      tmp[kk++] = arr[ii++];
    }
    else {
      tmp[kk++] = arr[jj++];
    }
  }
  
  while (ii < mid) {
    tmp[kk++] = arr[ii++];
  }
  while (jj < end) {
    tmp[kk++] = arr[jj++];
  }
  
  for (ii = beg; ii < end; ++ii) {
    arr[ii] = tmp[ii];
  }
}


static void msort_rec (int * arr, int * tmp, int beg, int end)
{
  size_t len, mid;
  
  len = end - beg;
  if (1 >= len) {
    return;
  }
  
  mid = beg + len / 2;
  msort_rec (arr, tmp, beg, mid);
  msort_rec (arr, tmp, mid, end);
  merge (arr, tmp, beg, mid, end);
}


static void merge_sort (int * arr, int len)
{
  int * tmp = malloc (len * sizeof(int));
  if (NULL == tmp) {
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  }
  msort_rec (arr, tmp, 0, len);
  free (tmp);
}


/***************************************************/

int main (int argc, char ** argv)
{
  sortfunc funcs[] = {
    { "merge sort", merge_sort }
  };
  return test_runall (funcs, sizeof(funcs) / sizeof(*funcs));
}
