#include "random.h"
#include "clockms.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


int * duplicate (int * arr, int len)
{
  int * tmp = malloc (len * sizeof *tmp);
  if (NULL == tmp)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  memcpy (tmp, arr, len * sizeof *tmp);
  return tmp;
}


void merge (int * arr, int * tmp, size_t beg, size_t mid, size_t end)
{
  size_t ii = beg;
  size_t jj = mid;
  size_t kk = beg;
  
  while (ii < mid && jj < end)
    if (arr[ii] < arr[jj])
      tmp[kk++] = arr[ii++];
    else
      tmp[kk++] = arr[jj++];
  
  while (ii < mid)
    tmp[kk++] = arr[ii++];
  while (jj < end)
    tmp[kk++] = arr[jj++];
  
  for (ii = beg; ii < end; ++ii)
    arr[ii] = tmp[ii];
}


void msort_rec (int * arr, int * tmp, int beg, int end)
{
  size_t len, mid;
  
  len = end - beg;
  if (1 >= len)
    return;
  
  mid = beg + len / 2;
  msort_rec (arr, tmp, beg, mid);
  msort_rec (arr, tmp, mid, end);
  merge (arr, tmp, beg, mid, end);
}


void merge_sort (int * arr, int len)
{
  int * tmp = malloc (len * sizeof *tmp);
  if (NULL == tmp)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  msort_rec (arr, tmp, 0, len);
  free (tmp);
}


void insertion_sort (int * arr, int len)
{
  int ii;
  for (ii = 1; ii < len; ++ii) {
    int jj, ival;
    ival = arr[ii];
    for (jj = ii; jj > 0; --jj) {
      if (ival >= arr[jj-1])
	break;
      arr[jj] = arr[jj-1];
    }
    arr[jj] = ival;
  }
}


int main (int argc, char ** argv)
{
  int dmin    =      0;
  int dmax    =   1000;
  int nstart  =    100;
  int nmax    = 150000;
  double nfac =      1.2;
  double nd;
  
  /*       12345678    12345678        12345678 */
  printf ("# length  merge_sort  insertion_sort\n");
  
  for (nd = nstart; nd <= nmax; nd *= nfac) {
    int nn, ii;
    int * data;
    int * dup;
    double tstart, tstop;
    
    nn = nd;
    
    data = random_create_uniform_array (dmin, dmax, nn);
    
    printf ("%8d", nn);
    fflush (stdout);
    
    dup = duplicate (data, nn);
    tstart = clockms ();
    merge_sort (dup, nn);
    tstop = clockms ();
    for (ii = 1; ii < nn; ++ii)
      if (dup[ii-1] > dup[ii])
	errx (EXIT_FAILURE, "merge_sort failed, dup[%d] == %d > %d == dup[%d]",
	      ii-1, dup[ii-1], dup[ii], ii);
    free (dup);
    printf ("    %8g", tstop - tstart);
    fflush (stdout);
    
    dup = duplicate (data, nn);
    tstart = clockms ();
    insertion_sort (dup, nn);
    tstop = clockms ();
    for (ii = 1; ii < nn; ++ii)
      if (dup[ii-1] > dup[ii])
	errx (EXIT_FAILURE, "insertion_sort failed, dup[%d] == %d > %d == dup[%d]",
	      ii-1, dup[ii-1], dup[ii], ii);
    free (dup);
    printf ("        %8g", tstop - tstart);
    fflush (stdout);
    
    printf ("\n");
    
    free (data);
  }
  
  return 0;
}
