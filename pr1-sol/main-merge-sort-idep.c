#include "random.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


/*
  Number of runs over which to collect timing measurements
 */
#define NRUNS 5


/*
  Merge sort implementation
*/


static void merge (int * arr, int * tmp, size_t beg, size_t mid, size_t end)
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


static void msort_rec (int * arr, int * tmp, int beg, int end)
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


/*
  Benchmark.
*/

int main (int argc, char ** argv)
{
  int dmin    =       0;
  int dmax    =    1000;
  int nstart  =     100;
  int nmax    = 1000000;
  double nfac =       1.2;
  double nd;
  int * data_rnd[NRUNS];
  int * data_asc[NRUNS];
  int * data_des[NRUNS];
  int * data_mix[NRUNS];
  int ** data[] = { data_rnd, data_asc, data_des, data_mix };
  int ii, jj;
  
  /*
    Allocate one big random input data array for every run. For
    varying the size, we will simply use a duplicate of the first N
    elements.
    
    (The fflush function asks the operating system to update the
    output from the previous printf commands, otherwise it waits until
    a newline is printed).
  */
  printf ("# generating input data");
  for (ii = 0; ii < NRUNS; ++ii) {
    int *asc, *des;
    printf (".");
    fflush (stdout);
    data_rnd[ii] = random_create_uniform_array (dmin, dmax, nmax);
    printf (".");
    fflush (stdout);
    data_asc[ii] = duplicate (data_rnd[ii], nmax);
    merge_sort (data_asc[ii], nmax);
    printf (".");
    fflush (stdout);
    data_des[ii] = malloc (nmax * sizeof **data_des);
    if (NULL == data_des[ii])
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    asc = data_asc[ii] + nmax - 1;
    des = data_des[ii];
    for (jj = 0; jj < nmax; ++jj)
      *(des++) = *(asc--);
    printf (".");
    fflush (stdout);
    data_mix[ii] = duplicate (data_rnd[ii], nmax);
    random_chunkwise_array (dmin, dmax, data_mix[ii], nmax, nstart / 2, nstart * 20, 'r');
  }
  
  printf ("\n"
	  "################################################\n"
	  "#\n"
	  "# merge sort runtime measurements\n"
	  "#\n"
	  "# column 1: N\n"
	  "# column 2: T min [ms] over random data\n"
	  "# column 3: T max [ms] over random data\n"
	  "# column 4: T min [ms] over ascending sorted data\n"
	  "# column 5: T max [ms] over ascending sorted data\n"
	  "# column 6: T min [ms] over descending sorted data\n"
	  "# column 7: T max [ms] over descending sorted data\n"
	  "# column 8: T min [ms] over chunkwise mixed sorted data\n"
	  "# column 9: T max [ms] over chunkwise mixed sorted data\n");
  
  /*
    Note that we use a floating point "length" so that we can easily
    create a geometric series for N. This spaces the sampled array
    sizes more densely for small N, and for big N (where things
    usually take much longer) we don't take so many samples (otherwise
    running the benchmark takes a really long time).
  */
  for (nd = nstart; nd <= nmax; nd *= nfac) {
    int nn;
    int * dup;
    
    /*
      convert the floating point "length" to an integer
    */
    nn = nd;
    
    printf ("%8d", nn);
    fflush (stdout);
    
    for (jj = 0; jj < sizeof data / sizeof *data; ++jj) {
      double tstart, tstop, tmin, tmax;
      tmin = -1;
      tmax = -1;
      for (ii = 0; ii < NRUNS; ++ii) {
	dup = duplicate (data[jj][ii], nn);
	
	tstart = clockms ();
	merge_sort (dup, nn);
	tstop = clockms ();
	
	free (dup);
	tstop -= tstart;
	
	if (0 > tmin || tstop < tmin)
	  tmin = tstop;
	if (0 > tmax || tstop > tmax)
	  tmax = tstop;
      }
      
      printf ("  %8g  %8g", tmin, tmax);
      fflush (stdout);
    }
    
    printf ("\n");
  }
  
  for (ii = 0; ii < NRUNS; ++ii)
    for (jj = 0; jj < sizeof data / sizeof *data; ++jj)
      free (data[jj][ii]);
  
  return 0;
}