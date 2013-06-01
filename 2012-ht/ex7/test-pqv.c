/*
 * test-pqv.c
 *
 * Unit tests for priority queues implemented via sorted and unsorted
 * vectors. See pqvu.h and pqvs.h for their interfaces.
 */

#include "pqvs.h"
#include "pqvu.h"
#include <stdio.h>
#include <err.h>


int main (int argc, char ** argv)
{
  int ii;
  IntVec *pqvu, *pqvs;
  pqvu = intvec_new (0);
  pqvs = intvec_new (0);
  
  if (2 > argc)
    errx (EXIT_FAILURE,
	  "Please provide a sequence of insertions.\n"
	  "For example, give the following command:\n"
	  "  %s 1 2 3 1 2 5 4 3",
	  argv[0]);
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, "failed to parse integer from argument %d `%s'", ii, argv[ii]);
    pqvu_insert (pqvu, num);
    pqvs_insert (pqvs, num);
    printf ("inserted %d\n", num);
    intvec_dump (pqvu, "  pqvu", stdout);
    intvec_dump (pqvs, "  pqvs", stdout);
  }
  
  printf ("--------------------------------------------------\n");
  while (0 < pqvu->len && 0 < pqvs->len) {
    int n1 = pqvu_extract (pqvu);
    int n2 = pqvs_extract (pqvs);
    if (n1 != n2)
      errx (EXIT_FAILURE, "oops, the queues don't agree (%d != %d)", n1, n2);
    fprintf (stderr, "extracted %d\n", n1);
    intvec_dump (pqvu, "  pqvu", stdout);
    intvec_dump (pqvs, "  pqvs", stdout);
  }
  
  if (pqvu->len != pqvs->len)
    errx (EXIT_FAILURE, "oops, one of the queues is not empty...");
  
  intvec_delete (pqvu);
  intvec_delete (pqvs);
  
  return 0;
}
