#include "uintheap.h"

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>


typedef unsigned int uint;


uint uniform (uint minval, uint maxval, int urnd)
{
  uint delta, tmp, mask;
  
  if (0 == (delta = maxval - minval))
    return minval;
  
  for (tmp = 1 << (8 * (sizeof delta) - 1); 0 == (tmp & delta); tmp >>= 1)
    /**/;
  for (mask = tmp; 0 != tmp; tmp >>= 1)
    mask |= tmp;

  for (;;) {
    if (sizeof tmp != read (urnd, &tmp, sizeof tmp))
      err (EXIT_FAILURE, __FILE__": %s: read", __func__);
    tmp &= mask;
    if (tmp <= delta)
      break;
  }
  
  return minval + tmp;
}


int main (int argc, char ** argv)
{
  int urnd;
  uint len = 1000;		/* total data length */
  uint chmin = 1;		/* minimum sorted chunk size */
  uint chmax = 1;		/* maximum sorted chunk size */
  char chdir = 'a';		/* ascending or descending chunks */
  /* uint swmin = 2;		/\* minimum number of swapped pairs *\/ */
  /* uint swmax = 5;		/\* maximum number of swapped pairs *\/ */
  uint nrem;
  
  if (1 < argc && 1 != sscanf (argv[1], "%u", &len))
    errx (EXIT_FAILURE, "invalid length `%s'", argv[1]);
  if (2 < argc && 1 != sscanf (argv[2], "%u", &chmin))
    errx (EXIT_FAILURE, "invalid minimum chunk size `%s'", argv[2]);
  if (3 < argc && 1 != sscanf (argv[3], "%u", &chmax))
    errx (EXIT_FAILURE, "invalid maximum chunk size `%s'", argv[3]);
  if (4 < argc) {
    switch (argv[4][0]) {
    case 'a': case 'A': chdir = 'a'; break;
    case 'd': case 'D': chdir = 'd'; break;
    default:
      errx (EXIT_FAILURE, "invalid sort direction `%s'", argv[4]);
    }
  }
  
  if (0 == chmin)
    chmin = 1;
  if (chmax < chmin)
    chmax = chmin;
  
  if (0 > (urnd = open ("/dev/urandom", O_RDONLY)))
    err (EXIT_FAILURE, "open /dev/urandom");
  
  printf ("# %u %u %u %c\n", len, chmin, chmax, chdir);
  
  for (nrem = len; 0 < nrem; /**/) {
    uint ch, jj;
    UintHeap *heap;

    ch = uniform (chmin, chmax, urnd);
    if (ch > nrem)
      ch = nrem;
    
    if ('a' == chdir)
      heap = uintheap_new_min (ch);
    else
      heap = uintheap_new_max (ch);
    
    for (jj = 0; jj < ch; ++jj) {
      uint num;
      if (sizeof num != read (urnd, &num, sizeof num))
	err (EXIT_FAILURE, __FILE__": %s: read /dev/urandom", __func__);
      uintheap_insert (heap, num);
    }
    
    for (jj = 0; jj < ch; ++jj)
      printf ("%u\n", uintheap_extract (heap));
    
    uintheap_delete (heap);
    nrem -= ch;
  }
  
  close (urnd);
  return 0;
}
