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
  uint chmin = 10;		/* minimum sorted chunk size */
  uint chmax = 200;		/* maximum sorted chunk size */
  char chdir = 'a';		/* ascending or descending chunks */
  /* uint swmin = 2;		/\* minimum number of swapped pairs *\/ */
  /* uint swmax = 5;		/\* maximum number of swapped pairs *\/ */
  uint nrem;
  
  if (0 > (urnd = open ("/dev/urandom", O_RDONLY)))
    err (EXIT_FAILURE, "open /dev/urandom");
  
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
