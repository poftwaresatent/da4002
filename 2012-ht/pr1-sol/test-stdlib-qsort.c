#include "random.h"
#include <stdio.h>
#include <stdlib.h>

#define LEN 1000

int compare_int (const void * lhs, const void * rhs)
{
  return *(int*) lhs - *(int*) rhs;
}

int main (int argc, char ** argv)
{
  int foo[LEN];
  int ii;
  
  random_uniform_array (0, 1000, foo, LEN);
  qsort (foo, LEN, sizeof *foo, compare_int);
  
  for (ii = 0; ii < LEN; ++ii)
    printf ("%d\n", foo[ii]);
  
  return 0;
}
