#include "ivs.h"
#include "ivu.h"
#include <stdio.h>
#include <err.h>


int main (int argc, char ** argv)
{
  int ii;
  IntVec *ivu, *ivs;
  ivu = intvec_new (0);
  ivs = intvec_new (0);
  
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
    ivu_insert (ivu, num);
    ivs_insert (ivs, num);
    printf ("inserted %d\n", num);
    intvec_dump (ivu, "  ivu", stdout);
    intvec_dump (ivs, "  ivs", stdout);
  }
  
  printf ("--------------------------------------------------\n");
  while (0 < ivu->len && 0 < ivs->len) {
    int n1 = ivu_extract (ivu);
    int n2 = ivs_extract (ivs);
    if (n1 != n2)
      errx (EXIT_FAILURE, "oops, the queues don't agree (%d != %d)", n1, n2);
    fprintf (stderr, "extracted %d\n", n1);
    intvec_dump (ivu, "  ivu", stdout);
    intvec_dump (ivs, "  ivs", stdout);
  }
  
  if (ivu->len != ivs->len)
    errx (EXIT_FAILURE, "oops, one of the queues is not empty...");
  
  intvec_delete (ivu);
  intvec_delete (ivs);
  
  return 0;
}
