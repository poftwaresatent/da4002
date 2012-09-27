#include "random.h"
#include "util.h"
#include "mergesort.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


/*
  Number of runs over which to collect timing measurements
 */
#define NRUNS 5


int main (int argc, char ** argv)
{
  int dmin    =       0;
  int dmax    =    1000;
  int nstart  =     100;
  int nmax    = 1000000;
  double nfac =       1.2;
  double nd;
  int * data[NRUNS];
  int ii;
  
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
    printf (".");
    fflush (stdout);
    data[ii] = random_create_uniform_array (dmin, dmax, nmax);
  }
  
  printf ("\n"
	  "################################################\n"
	  "#\n"
	  "# merge sort runtime measurements\n"
	  "#\n"
	  "# column 1:         N\n"
	  "# columns %d to %d: T [ms] of individual runs\n"
	  "# column %d:        minimum T\n"
	  "# column %d:        average T\n"
	  "# column %d:        maximum T\n",
	  2, NRUNS + 1, NRUNS + 2, NRUNS + 3, NRUNS + 4);
  
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
    double tstart, tstop, tmin, tmax, tsum;
    
    /*
      convert the floating point "length" to an integer
    */
    nn = nd;
    
    printf ("%8d", nn);
    fflush (stdout);
    
    tmin = -1;
    tmax = -1;
    tsum = 0;
    for (ii = 0; ii < NRUNS; ++ii) {
      dup = duplicate (data[ii], nn);
      
      tstart = clockms ();
      mergesort (dup, nn);
      tstop = clockms ();
      
      free (dup);
      tstop -= tstart;
      printf ("  %8g", tstop);
      fflush (stdout);
      
      if (0 > tmin || tmin < tstop)
	tmin = tstop;
      if (0 > tmax || tmax > tstop)
	tmax = tstop;
      tsum += tstop;
    }
    
    printf ("  %8g  %8g  %8g\n", tmin, tsum/NRUNS, tmax);
  }
  
  for (ii = 0; ii < NRUNS; ++ii)
    free (data[ii]);
  
  return 0;
}
