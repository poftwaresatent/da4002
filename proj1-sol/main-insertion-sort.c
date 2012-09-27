#include "random.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


/*
  Insertion sort implementation
*/


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


/*
  Benchmark.
*/

int main (int argc, char ** argv)
{
  int dmin    =       0;
  int dmax    =    1000;
  int nstart  =      20;
  int nmax    =   50000;
  double nfac =       1.2;
  double nd;
  int * data;
  
  /*
    Allocate one big random input data array. For varying the size, we
    will simply use a duplicate of the first N elements.
  */
  printf ("# generating input data (this can take a while...)\n");
  data = random_create_uniform_array (dmin, dmax, nmax);
  
  printf ("################################################\n"
	  "#\n"
	  "# insertion sort runtime measurements\n"
	  "#\n"
	  "# column 1: N\n"
	  "# column 2: T [ms]\n"
	  "#\n");
  
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
    double tstart, tstop;
    
    /*
      convert the floating point "length" to an integer
    */
    nn = nd;
    
    printf ("%8d", nn);
    fflush (stdout);
    
    dup = duplicate (data, nn);
    
    tstart = clockms ();
    insertion_sort (dup, nn);
    tstop = clockms ();
    
    free (dup);
    
    printf ("  %8g\n", tstop - tstart);
  }
  
  free (data);
  
  return 0;
}
