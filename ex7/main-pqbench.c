#include "pqvs.h"
#include "pqvu.h"
#include "pqbst.h"
#include "random.h"
#include <err.h>
#include <time.h>


static void benchmark (void * cont,
		       void (*insert)(void*, int), int (*extract)(void*), int (*nonempty)(void*),
		       size_t nstart, size_t nmax, double nfac)
{
  double nd;
  
  if (nfac <= 1.0)
    nfac = 1.1;
  
  /*       12345\t12345678  12345678  12345678  12345678 */
  printf ("#   N\t   T tot     T ins    T both     T ext\n");
  for (nd = nstart; nd <= nmax; nd *= nfac) {
    size_t nn, ii;
    int *arr, *num;
    clock_t tt[4];
    
    nn = nd;
    
    if (NULL == (arr = malloc (2 * nn * sizeof *arr)))
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    random_uniform_array (-1000, 1000, arr, nn);
    
    printf ("%5zu", nn);
    fflush (stdout);
    
    num = arr;
    tt[0] = clock ();
    for (ii = 0; ii < nn; ++ii)
      insert (cont, *(num++));
    tt[1] = clock ();
    for (ii = 0; ii < nn; ++ii) {
      extract (cont);
      insert (cont, *(num++));
    }
    tt[2] = clock ();
    while (nonempty (cont))
      extract (cont);
    tt[3] = clock ();
    printf ("\t%8ld  %8ld  %8ld  %8ld\n",
	    tt[3] - tt[0],
	    tt[1] - tt[0],
	    tt[2] - tt[1],
	    tt[3] - tt[2]);
    
    free (arr);    
  }

}


int main (int argc, char ** argv)
{
  size_t nstart = 10;
  size_t nmax = 30000;
  double nfac = 1.4142;
  
  IntVec *pqvu, *pqvs;
  PqBST *bst;
  
  pqvu = intvec_new (nmax);
  pqvs = intvec_new (nmax);
  bst = pqbst_new ();
  
  printf ("# vector with unsorted insertion\n");
  benchmark (pqvu, pqvu_insert, pqvu_extract, intvec_nonempty, nstart, nmax, nfac);
  
  printf ("\n\n# vector with sorted insertion\n");
  benchmark (pqvs, pqvs_insert, pqvs_extract, intvec_nonempty, nstart, nmax, nfac);
  
  printf ("\n\n# binary search tree\n");
  benchmark (bst, pqbst_insert, pqbst_extract, pqbst_nonempty, nstart, nmax, nfac);
  
  return 0;
}
