/*
 * util.c
 *
 * Implementation of the utility functions.
 */

#include <sys/time.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>


double clockms (void)
{
  static struct timeval t0 = { 0, 0 };
  struct timeval t1;
  
  if (0 == t0.tv_sec)
    if (0 != gettimeofday (&t0, NULL))
      err (EXIT_FAILURE, __FILE__": %s: gettimeofday", __func__);
  if (0 != gettimeofday (&t1, NULL))
    err (EXIT_FAILURE, __FILE__": %s: gettimeofday", __func__);
  
  return 1e3 * (t1.tv_sec - t0.tv_sec) + 1e-3 * (t1.tv_usec - t0.tv_usec);
}


int * duplicate (int * arr, int len)
{
  int * dup = malloc (len * sizeof *dup);
  if (NULL == dup)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  memcpy (dup, arr, len * sizeof *dup);
  return dup;
}
