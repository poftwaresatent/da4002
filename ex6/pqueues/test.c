#include "sorted.h"
#include "unsorted.h"
#include <stdio.h>
#include <err.h>


int main (int argc, char ** argv)
{
  int ii;
  IntVec *unsorted, *sorted;
  unsorted = intvec_new ();
  sorted = intvec_new ();
  
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
    unsorted_insert (unsorted, num);
    sorted_insert (sorted, num);
    printf ("inserted %d\n", num);
    intvec_dump (unsorted, "  unsorted", stdout);
    intvec_dump (sorted, "  sorted", stdout);
  }
  
  printf ("--------------------------------------------------\n");
  while (0 < unsorted->len && 0 < sorted->len) {
    int n1 = unsorted_extract (unsorted);
    int n2 = sorted_extract (sorted);
    if (n1 != n2)
      errx (EXIT_FAILURE, "oops, the queues don't agree (%d != %d)", n1, n2);
    fprintf (stderr, "extracted %d\n", n1);
    intvec_dump (unsorted, "  unsorted", stdout);
    intvec_dump (sorted, "  sorted", stdout);
  }
  
  if (unsorted->len != sorted->len)
    errx (EXIT_FAILURE, "oops, one of the queues is not empty...");
  
  intvec_delete (unsorted);
  intvec_delete (sorted);
  
  return 0;
}
