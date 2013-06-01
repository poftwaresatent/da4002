/*
 * random.c
 *
 * Implementation of utility functions for creating random data.
 */

#include "random.h"

#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>


void random_read (void * buf, size_t nbytes)
{
  static int fd = -1;
  if (0 > fd && 0 > (fd = open ("/dev/urandom", O_RDONLY)))
    err (EXIT_FAILURE, __FILE__": %s: open /dev/urandom", __func__);
  if (nbytes != read (fd, buf, nbytes))
    err (EXIT_FAILURE, __FILE__": %s: read /dev/urandom", __func__);
}


int random_uniform (int minval, int maxval)
{
  unsigned int delta, tmp, mask;
  
  if (maxval < minval) {
    tmp = minval;
    minval = maxval;
    maxval = tmp;
  }
    
  if (0 == (delta = maxval - minval))
    return minval;
  
  for (tmp = 1 << (8 * (sizeof delta) - 1); 0 == (tmp & delta); tmp >>= 1)
    /**/;
  for (mask = tmp; 0 != tmp; tmp >>= 1)
    mask |= tmp;

  for (;;) {
    random_read (&tmp, sizeof tmp);
    tmp &= mask;
    if (tmp <= delta)
      break;
  }
  
  return minval + tmp;
}


void random_uniform_array  (int minval, int maxval, int * arr, size_t len)
{
  for (/**/; len > 0; ++arr, --len)
    *arr = random_uniform (minval, maxval);
}
