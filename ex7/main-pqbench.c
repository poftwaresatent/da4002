#include "pqvs.h"
#include "pqvu.h"
#include "pqbst.h"
#include "intheap.h"
#include "random.h"
#include <err.h>
#include <time.h>


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
    clock_t tt[3];
    
    nn = nd;
    
    if (NULL == (arr = malloc (2 * nn * sizeof *arr)))
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    random_uniform_array (0, pmax, arr, nn);
    
    printf ("%8zu", nn);
    fflush (stdout);
    
    num = arr;
    for (ii = 0; ii < nn; ++ii)
      insert (cont, *(num++));
    
    tt[0] = clock ();
    for (ii = 0; ii < navg; ++ii)
      insert (cont, *(num++));
    tt[1] = clock ();
    for (ii = 0; ii < navg; ++ii)
      extract (cont);
    tt[2] = clock ();
    
    while (nonempty (cont))
      extract (cont);
    
    printf ("\t%8.3f  %8.3f  %8.3f\n",
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
  
  IntVec *pqvu, *pqvs;
  PqBST *bst;
  IntHeap * heap;
  
  printf ("##################################################\n"
  	  "# vector with unsorted insertion, extraction based on find_max\n");
  pqvu = intvec_new (nmax);
  benchmark (pqvu, pqvu_insert, pqvu_extract, intvec_nonempty, nstart, nmax, navg, nfac, 10000);
  intvec_delete (pqvu);
  
  printf ("\n\n##################################################\n"
  	  "# vector with sorted insertion, extraction from the end\n");
  pqvs = intvec_new (nmax);
  benchmark (pqvs, pqvs_insert, pqvs_extract, intvec_nonempty, nstart, nmax, navg, nfac, 10000);
  intvec_delete (pqvs);

  nstart =   50000;
  nmax =   5000000;
  navg =      1000;
  
  printf ("\n\n##################################################\n"
	  "# binary search tree (pmax = 1000)\n");
  bst = pqbst_new ();
  benchmark (bst, pqbst_insert, pqbst_extract, pqbst_nonempty, nstart, nmax, navg, nfac, 1000);
  pqbst_delete (bst);
  
  printf ("\n\n##################################################\n"
	  "# binary search tree (pmax = 10000)\n");
  bst = pqbst_new ();
  benchmark (bst, pqbst_insert, pqbst_extract, pqbst_nonempty, nstart, nmax, navg, nfac, 10000);
  pqbst_delete (bst);
  
  printf ("\n\n##################################################\n"
	  "# heap\n");
  heap = intheap_new (nmax);
  benchmark (heap, intheap_insert, intheap_extract, intheap_nonempty, nstart, nmax, navg, nfac, 1000);
  intheap_delete (heap);
  
  return 0;
}
