#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


int fiboMemo (int ii)
{
  static int * memo = NULL;
  static int imax = 0;
  int fi;
  
  if (NULL == memo) {
    printf ("%2d:  initialize\n", ii);
    if (NULL == (memo = malloc (2 * sizeof *memo)))
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    memo[0] = 1;
    memo[1] = 1;
    imax = 1;
  }
  
  if (ii <= imax)
    fi = memo[ii];
  else {
    printf ("%2d:  grow\n", ii);
    if (NULL == (memo = realloc (memo, (ii+1) * sizeof *memo)))
      err (EXIT_FAILURE, __FILE__": %s: realloc", __func__);
    memset (memo + imax + 1, 0, (ii - imax) * sizeof *memo);
    imax = ii;
    fi = 0;
  }
  
  if (0 < fi) {
    printf ("%2d:  looked up F_%d=%d\n", ii, ii, fi);
    return fi;
  }
  
  printf ("%2d:  compute F_%d + F_%d ...\n", ii, ii-1, ii-2);
  fi = fiboMemo (ii-1) + fiboMemo (ii-2);
  
  memo[ii] = fi;
  return fi;
}


int main (int argc, char ** argv)
{
  fiboMemo (6);
  return 0;
}
