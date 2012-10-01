#include "random.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


int compare_int (const void * lhs, const void * rhs)
{
  return *(int*) lhs - *(int*) rhs;
}


/*
  Benchmark.
*/

int main (int argc, char ** argv)
{
  int dmin    =        0;
  int dmax    =     1000;
  int nstart  =     5000;
  int nmax    = 10000000;
  double nfac =       1.2;
  double nd;
  int * data;
  
  /*
    Allocate one big random input data array. For varying the size, we
    will simply use a duplicate of the first N elements.
  */
  printf ("# generating input data (this can take a while...)\n");
  fflush (stdout);
  data = random_create_uniform_array (dmin, dmax, nmax);
  
  printf ("################################################\n"
	  "#\n"
	  "# Darwin builtin sorting functions runtime measurements\n"
	  "#\n"
	  "# column 1: N\n"
	  "# column 2: heapsort T [ms]\n"
	  "# column 3: mergesort T [ms]\n"
	  "# column 4: qsort T [ms]\n"
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
    heapsort (dup, nn, sizeof *dup, compare_int);
    tstop = clockms ();
    free (dup);
    printf ("  %8g", tstop - tstart);
    
    dup = duplicate (data, nn);
    tstart = clockms ();
    mergesort (dup, nn, sizeof *dup, compare_int);
    tstop = clockms ();
    free (dup);
    printf ("  %8g", tstop - tstart);
    
    dup = duplicate (data, nn);
    tstart = clockms ();
    qsort (dup, nn, sizeof *dup, compare_int);
    tstop = clockms ();
    free (dup);
    printf ("  %8g\n", tstop - tstart);
  }
  
  free (data);
  
  return 0;
}
