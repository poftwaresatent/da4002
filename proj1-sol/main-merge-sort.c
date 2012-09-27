#include "random.h"
#include "util.h"
#include "merge_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


int main (int argc, char ** argv)
{
  int dmin    =       0;
  int dmax    =    1000;
  int nstart  =     100;
  int nmax    = 1000000;
  double nfac =       1.2;
  double nd;
  int * data;
  
  /*
    Allocate one big random input data array. For the varying the size,
    we will simply use a duplicate of the first N elements.
  */
  data = random_create_uniform_array (dmin, dmax, nmax);
  
  printf ("################################################\n"
	  "# merge sort runtime measurements\n"
	  /* 12345678    12345678 */
	  "#        N      T [ms]\n");
  
  /*
    the fflush function asks the operating system to update the output
    from the previous printf commands (otherwise it can sometimes wait
    quite a bit).
  */
  fflush (stdout);
  
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
    merge_sort (dup, nn);
    tstop = clockms ();
    free (dup);
    printf ("    %8g", tstop - tstart);
    fflush (stdout);
    
    printf ("\n");
    
  }
  
  free (data);
  return 0;
}
