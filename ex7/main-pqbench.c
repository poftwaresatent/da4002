#include "ivs.h"
#include "ivu.h"
#include "intbst.h"
#include "random.h"
#include <err.h>
#include <time.h>


int main (int argc, char ** argv)
{
  size_t nn;
  
  for (nn = 10; nn < 30000; nn *= 2) {
    size_t ii;
    int *arr, *num;
    IntVec *ivu, *ivs;
    clock_t tt[4];
    
    if (NULL == (arr = malloc (2 * nn * sizeof *arr)))
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    ivu = intvec_new ();
    ivs = intvec_new ();
    
    random_uniform_array (-1000, 1000, arr, nn);
    
    printf ("%5zu", nn);
    fflush (stdout);
    
    /* integer vector, unsorted */
    
    num = arr;
    tt[0] = clock ();
    for (ii = 0; ii < nn; ++ii)
      ivu_insert (ivu, *(num++));
    tt[1] = clock ();
    for (ii = 0; ii < nn; ++ii) {
      ivu_extract (ivu);
      ivu_insert (ivu, *(num++));
    }
    tt[2] = clock ();
    while (0 < ivu->len)
      ivu_extract (ivu);
    tt[3] = clock ();
    printf ("\t%8ld  %8ld  %8ld  %8ld",
	    tt[3] - tt[0],
	    tt[1] - tt[0],
	    tt[2] - tt[1],
	    tt[3] - tt[2]);
    fflush (stdout);
    
    /* integer vector, sorted */
    
    num = arr;
    tt[0] = clock ();
    for (ii = 0; ii < nn; ++ii)
      ivs_insert (ivs, *(num++));
    tt[1] = clock ();
    for (ii = 0; ii < nn; ++ii) {
      ivs_extract (ivs);
      ivs_insert (ivs, *(num++));
    }
    tt[2] = clock ();
    while (0 < ivs->len)
      ivs_extract (ivs);
    tt[3] = clock ();
    printf ("\t%8ld  %8ld  %8ld  %8ld",
	    tt[3] - tt[0],
	    tt[1] - tt[0],
	    tt[2] - tt[1],
	    tt[3] - tt[2]);
    fflush (stdout);
    
    printf ("\n");
    
    intvec_delete (ivu);
    intvec_delete (ivs);
    free (arr);    
  }
  
  return 0;
}
