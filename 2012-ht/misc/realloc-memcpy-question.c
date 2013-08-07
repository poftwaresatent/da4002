#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define BLOCKSIZE 512


int main (int argc, char ** argv)
{
  int *buf, ii;
  size_t bufsize;
  
  buf = malloc (BLOCKSIZE * sizeof(int));
  if (NULL == buf)
    err (EXIT_FAILURE, "malloc");
  
  for (ii = 0; ii < BLOCKSIZE; ++ii)
    buf[ii] = ii;
  
  for (bufsize = 2 * BLOCKSIZE; ; bufsize += BLOCKSIZE) {
    int *tmp = realloc (buf, bufsize * sizeof(int));
    if (NULL == tmp) {
      free (buf);
      err (EXIT_FAILURE, "realloc");
    }
    if (tmp == buf)
      fprintf (stderr, ".");
    else {
      fprintf (stderr, "\nallocation changed, let's check for mismatches\n");
      for (ii = 0; ii < BLOCKSIZE; ++ii)
	if (tmp[ii] != buf[ii])
	  fprintf (stderr, "  MISMATCH: you need memcpy after realloc!\n");
      free (tmp);
      break;
    }
  }
  
  return 0;
}
