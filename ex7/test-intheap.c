/*
 * test-intheap.c
 *
 * Unit tests for intheap.{h,c}
 */

#include "intheap.h"

#include <err.h>
#include <stdlib.h>


int main (int argc, char ** argv)
{
  int ii;
  IntHeap *heap;
  
  intheap_debug_on ();
  
  heap = intheap_new (argc);
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, __FILE__": argument %d `%s' is not an integer", ii, argv[ii]);
    intheap_insert (heap, num);
    fprintf (stdout, "inserted %d\n  ", num);
    intheap_dump (heap, stdout);
  }
  
  fprintf (stdout,"--------------------------------------------------\n");
  while (0 < heap->len) {
    int num = intheap_extract (heap);
    fprintf (stdout, "extracted %d\n  ", num);
    intheap_dump (heap, stdout);
  }
  
  intheap_delete (heap);
  
  return 0;
}
