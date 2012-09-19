#include "strheap.h"

#include <string.h>
#include <err.h>
#include <stdlib.h>


int main (int argc, char ** argv)
{
  int ii;
  StrHeap *heap;
  
  heap = strheap_new ();
  
  for (ii = 1; ii < argc; ++ii) {
    char * str;
    if (NULL == (str = strdup (argv[ii])))
      err (EXIT_FAILURE, "strdup failed on argument %d `%s'", ii, argv[ii]);
    strheap_insert (heap, str);
    fprintf (stderr, "inserted %s\n  ", str);
    strheap_dump (heap, stderr);
  }
  
  fprintf (stderr,"--------------------------------------------------\n");
  while (0 < heap->len) {
    char * str = strheap_extract (heap);
    fprintf (stderr, "extracted %s\n  ", str);
    strheap_dump (heap, stderr);
    free (str);
  }
  
  strheap_delete (heap);
  
  return 0;
}

