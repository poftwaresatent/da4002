/*
 * main-pqbench.c
 *
 * Implementation of the priority queue benchmarking application. Runs
 * a series of insertions and extractions on various implementations
 * of priority queues, and measures the time it takes in function of
 * the input data size and the particular queue implementation. Prints
 * the data to standard output in a format that is suitable for
 * gnuplot.
 *
 * The easiest way to safe the data produced by this benchmark to a
 * text file is to redirect standard output from the command
 * line. This is best done through the `tee' command, which echoes
 * each measurement onto the cosole as well as saving it in a
 * file. For example, to safe everything in a file called data.txt,
 * just launch the benchmark like this:
 *
 *   ./main-pqbench | tee data.txt
 *
 * Then you can plot the data with gnuplot using the following
 * approach:
 *
 *   cd /path/to/the/directory/where/data.txt/is/stored
 *   gnuplot
 *   plot 'data.txt' index 0 using 1:2 with lines title 'unsorted vector insert'
 *
 */

#include "pqvs.h"
#include "pqvu.h"
#include "intheap.h"
#include "random.h"
#include "clockms.h"
#include <err.h>


static void benchmark (void * cont,
		       void (*insert)(void*, int), int (*extract)(void*), int (*nonempty)(void*),
		       size_t nstart, size_t nmax, size_t navg, double nfac,
		       int pmax)
{
  double nd;
  double davg;
  
  if (1 > nstart)
    nstart = 1;
  if (nmax < nstart)
    nmax = nstart;
  if (1 >= navg)
    navg = 1;
  if (nstart < navg)
    navg = nstart;
  if (nfac <= 1.0)
    nfac = 1.1;
  davg = 1.0 / navg;
  
  /*         12345678\t12345678  12345678  12345678 */
  printf ("# average operation times (over %zu samples) after N insertions\n"
	  "#        N\t  insert   extract     total\n",
	  navg);
  
  for (nd = nstart; nd <= nmax; nd *= nfac) {
    size_t nn, ii;
    int *arr, *num;
    double tt[3];
    
    nn = nd;
    
    if (NULL == (arr = malloc (2 * nn * sizeof *arr)))
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    random_uniform_array (0, pmax, arr, nn);
    
    printf ("%8zu", nn);
    fflush (stdout);
    
    num = arr;
    for (ii = 0; ii < nn; ++ii)
      insert (cont, *(num++));
    
    tt[0] = clockms ();
    for (ii = 0; ii < navg; ++ii)
      insert (cont, *(num++));
    tt[1] = clockms ();
    for (ii = 0; ii < navg; ++ii)
      extract (cont);
    tt[2] = clockms ();
    
    while (nonempty (cont))
      extract (cont);
    
    printf ("\t%8g  %8g  %8g\n",
	    davg * (tt[1] - tt[0]),
	    davg * (tt[2] - tt[1]),
	    davg * (tt[2] - tt[0]));
    
    free (arr);    
  }
  
}


int main (int argc, char ** argv)
{
  size_t nstart =   500;
  size_t nmax   = 40000;
  size_t navg   =   100;
  double nfac   =     1.4142;
  int pmax      =  1000;
  
  IntVec *pqvu, *pqvs;
  IntHeap * heap;
  
  printf ("##################################################\n"
  	  "# vector with unsorted insertion, extraction based on find_max\n");
  pqvu = intvec_new (nmax);
  benchmark (pqvu,
	     /*
	      * This line looks really cryptic, but it's just a
	      * pointer cast to eliminate a compiler warning.  If
	      * you're curious about the details: The
	      * "(void(*)(void*,int))" is a function pointer type,
	      * which is slightly different but compatible to the type
	      * of the function pqvu_insert. We can also just write
	      * pqvu_insert without that complicated-looking cast, but
	      * gcc will then complain about incompatible pointer
	      * types.
	      *
	      * The same remarks are valid for pqvu_extract and
	      * intvec_nonempty, and also for the other places where
	      * we call the benchmark function. Don't worry, you're
	      * not expected to be able to write such code in order to
	      * pass this course...
	      */
	     (void(*)(void*,int)) pqvu_insert,
	     (int(*)(void*)) pqvu_extract,
	     (int(*)(void*)) intvec_nonempty,
	     nstart, nmax, navg, nfac, pmax);
  intvec_delete (pqvu);
  
  printf ("\n\n##################################################\n"
  	  "# vector with sorted insertion, extraction from the end\n");
  pqvs = intvec_new (nmax);
  benchmark (pqvs,
	     (void(*)(void*,int)) pqvs_insert,
	     (int(*)(void*)) pqvs_extract,
	     (int(*)(void*)) intvec_nonempty,
	     nstart, nmax, navg, nfac, pmax);
  intvec_delete (pqvs);

  nstart =   5000;
  nmax =   500000;
  navg =      500;
  
  printf ("\n\n##################################################\n"
	  "# heap\n");
  heap = intheap_new (nmax);
  benchmark (heap,
	     (void(*)(void*,int)) intheap_insert,
	     (int(*)(void*)) intheap_extract,
	     (int(*)(void*)) intheap_nonempty,
	     nstart, nmax, navg, nfac, pmax);
  intheap_delete (heap);
  
  printf ("\n\n##################################################"
	  "# things you may want to plot with this data\n"
	  "# assuming you've saved it as data.txt\n"
	  "#\n"
	  "#   plot 'data.txt' i 0 u 1:2 w l t 'unsorted vector insertion'\n"
	  "#   plot 'data.txt' i 0 u 1:3 w l t 'unsorted vector extraction'\n"
	  "#   plot 'data.txt' i 0 u 1:3 w l t 'unsorted vector total'\n"
	  "#\n"
	  "#   plot 'data.txt' i 1 u 1:2 w l t 'sorted vector insertion'\n"
	  "#   plot 'data.txt' i 1 u 1:3 w l t 'sorted vector extraction'\n"
	  "#   plot 'data.txt' i 1 u 1:4 w l t 'sorted vector total'\n"
	  "#\n"
	  "#   plot 'data.txt' i 2 u 1:2 w l t 'heap insertion'\n"
	  "#   plot 'data.txt' i 2 u 1:3 w l t 'heap extraction'\n"
	  "#   plot 'data.txt' i 2 u 1:4 w l t 'heap total'\n"
	  "#\n"
	  "# You can also compare measurement with theory, for example:\n"
	  "#\n"
	  "#   plot 'data.txt' i 2 u 1:($4/$1) w l t 'heap / O(N)'\n"
	  "#   plot 'data.txt' i 2 u 1:($4/log($1)) w l t 'heap / O(log N)'\n"
	  "#   plot 'data.txt' i 2 u 1:($4/($1*log($1))) w l t 'heap / O(N log N)'\n"
	  "#\n"
	  "# You probably need to run more extensive tests and takes some averages\n"
	  "# from multiple runs to get meaningful comparions. Note that you can\n"
	  "# plot multiple data series by giving plot commands that have several\n"
	  "# comma-separated entries, such as:\n"
	  "#\n"
	  "#   plot 'data1.txt' i 2 u 1:4 w l t 'run1', 'data2.txt' i 2 u 1:4 w l t 'run2'\n");
  
  return 0;
}
