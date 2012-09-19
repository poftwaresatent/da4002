#include "intvector.h"

#include <stdio.h>
/* #include <stdlib.h> */
#include <err.h>


void pq1_insert (IntVector * vec, int num)
{
  intvector_ins (vec, vec->len, num);
}


int pq1_extract (IntVector * vec)
{
  size_t pos;
  if ( ! intvector_findmax (vec, &pos))
    errx (EXIT_FAILURE, "pq1_extract: intvector_findmax failed (empty vector?)");
  return intvector_rem (vec, pos);
}


void pq2_insert (IntVector * vec, int num)
{
  intvector_ins_desc (vec, num);
}


int pq2_extract (IntVector * vec)
{
  return intvector_rem (vec, 0);
}


int main (int argc, char ** argv)
{
  int ii;
  IntVector *pq1, *pq2;
  pq1 = intvector_new ();
  pq2 = intvector_new ();
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, "failed to parse integer from argument %d `%s'", ii, argv[ii]);
    pq1_insert (pq1, num);
    pq2_insert (pq2, num);
    printf ("inserted %d\n", num);
    intvector_dump (pq1, "  pq1", stdout);
    intvector_dump (pq2, "  pq2", stdout);
  }
  
  printf ("--------------------------------------------------\n");
  while (0 < pq1->len && 0 < pq2->len) {
    int n1 = pq1_extract (pq1);
    int n2 = pq2_extract (pq2);
    if (n1 != n2)
      errx (EXIT_FAILURE, "oops, the queues don't agree (%d != %d)", n1, n2);
    fprintf (stderr, "extracted %d\n", n1);
    intvector_dump (pq1, "  pq1", stdout);
    intvector_dump (pq2, "  pq2", stdout);
  }
  
  if (pq1->len != pq2->len)
    errx (EXIT_FAILURE, "oops, one of the queues is not empty...");
  
  intvector_delete (pq1);
  intvector_delete (pq2);
  
  return 0;
}
