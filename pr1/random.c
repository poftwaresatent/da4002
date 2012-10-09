/*
 * random.c
 *
 * Implementation of utility functions for creating random data.
 */

#include "random.h"

#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>


void random_read (void * buf, size_t nbytes)
{
  static int fd = -1;
  if (0 > fd && 0 > (fd = open ("/dev/urandom", O_RDONLY)))
    err (EXIT_FAILURE, __FILE__": %s: open /dev/urandom", __func__);
  if (nbytes != read (fd, buf, nbytes))
    err (EXIT_FAILURE, __FILE__": %s: read /dev/urandom", __func__);
}


int random_uniform (int minval, int maxval)
{
  unsigned int delta, tmp, mask;
  
  if (maxval < minval) {
    tmp = minval;
    minval = maxval;
    maxval = tmp;
  }
    
  if (0 == (delta = maxval - minval))
    return minval;
  
  for (tmp = 1 << (8 * (sizeof delta) - 1); 0 == (tmp & delta); tmp >>= 1)
    /**/;
  for (mask = tmp; 0 != tmp; tmp >>= 1)
    mask |= tmp;

  for (;;) {
    random_read (&tmp, sizeof tmp);
    tmp &= mask;
    if (tmp <= delta)
      break;
  }
  
  return minval + tmp;
}


void random_uniform_array  (int minval, int maxval, int * arr, size_t len)
{
  for (/**/; len > 0; ++arr, --len)
    *arr = random_uniform (minval, maxval);
}


int * random_create_uniform_array (int minval, int maxval, size_t len)
{
  int * arr = malloc (len * sizeof *arr);
  if (NULL == arr)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  random_uniform_array (minval, maxval, arr, len);
  return arr;
}


static void merge_asc (int * dst, int * src, size_t beg, size_t mid, size_t end)
{
  size_t ii = beg;
  size_t jj = mid;
  size_t kk = beg;
  
  while (ii < mid && jj < end)
    if (src[ii] < src[jj])
      dst[kk++] = src[ii++];
    else
      dst[kk++] = src[jj++];
  while (ii < mid)
    dst[kk++] = src[ii++];
  while (jj < end)
    dst[kk++] = src[jj++];
}


static void merge_des (int * dst, int * src, size_t beg, size_t mid, size_t end)
{
  size_t ii = beg;
  size_t jj = mid;
  size_t kk = beg;
  
  while (ii < mid && jj < end)
    if (src[ii] > src[jj])
      dst[kk++] = src[ii++];
    else
      dst[kk++] = src[jj++];
  while (ii < mid)
    dst[kk++] = src[ii++];
  while (jj < end)
    dst[kk++] = src[jj++];
}


static void msort_gen (int * arr, int * tmp, size_t beg, size_t end,
		       void (*merge)(int*,int*,size_t,size_t,size_t))
{
  size_t len, mid;
  
  len = end - beg;
  if (1 >= len)
    return;
  
  mid = beg + len / 2;
  
  /* trick to avoid copy:
     - swap arr and tmp in recursion
     - merge tmp into arr
     BUT THIS ONLY WORKS if tmp is a DUPLICATE of arr when the
     recursion is entered!!!
  */	
  
  msort_gen (tmp, arr, beg, mid, merge);
  msort_gen (tmp, arr, mid, end, merge);
  
  merge (arr, tmp, beg, mid, end);
}


static void msort_asc(int * arr, int * tmp, size_t beg, size_t end)
{
  msort_gen (arr, tmp, beg, end, merge_asc);
}


static void msort_des(int * arr, int * tmp, size_t beg, size_t end)
{
  msort_gen (arr, tmp, beg, end, merge_des);
}


static void msort_rnd(int * arr, int * tmp, size_t beg, size_t end)
{
  if (random_uniform (0, 1) > 0)
    msort_gen (arr, tmp, beg, end, merge_asc);
  else
    msort_gen (arr, tmp, beg, end, merge_des);
}


void random_chunkwise_array (int minval, int maxval, int * arr, size_t len,
			     size_t chunkmin, size_t chunkmax, char chunkdir)
{
  size_t beg;
  int * tmp;
  void (*msort)(int*,int*,size_t,size_t);
  
  tmp = malloc (len * sizeof *tmp);
  if (NULL == tmp)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  
  if (0 == chunkmin)
    chunkmin = 1;
  if (chunkmax < chunkmin)
    chunkmax = chunkmin;
  if (chunkmin > INT_MAX)
    chunkmin = INT_MAX;
  if (chunkmax > INT_MAX)
    chunkmax = INT_MAX;
  
  switch (chunkdir) {
  case 'a':
  case 'A':
    msort = msort_asc;
    break;
  case 'd':
  case 'D':
    msort = msort_des;
    break;
  default:
    msort = msort_rnd;
  }
  
  random_uniform_array (minval, maxval, arr, len);
  /* make duplicate to allow pointer switch trick in merge sort */  
  memcpy (tmp, arr, len * sizeof *tmp);
  
  for (beg = 0; beg < len; /**/) {
    size_t end = beg + random_uniform (chunkmin, chunkmax);
    if (end > len)
      end = len;
    msort (arr, tmp, beg, end);
    if (msort_des == msort) {
      size_t jj;
      for (jj = beg+1; jj < end; ++jj)
	if (arr[jj-1] < arr[jj])
	  errx (EXIT_FAILURE, "msort_des failed, arr[%zu] == %d < %d == arr[%zu]",
		jj-1, arr[jj-1], arr[jj], jj);
    }
    else if (msort_asc == msort) {
      size_t jj;
      for (jj = beg+1; jj < end; ++jj)
	if (arr[jj-1] > arr[jj])
	  errx (EXIT_FAILURE, "msort_asc failed, arr[%zu] == %d > %d == arr[%zu]",
		jj-1, arr[jj-1], arr[jj], jj);
    }
    beg = end;
  }
  
  free (tmp);
}
