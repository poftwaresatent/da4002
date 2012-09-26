#include "random.h"
#include <stdio.h>

#define LEN 1000

int main (int argc, char ** argv)
{
  int foo[LEN];
  int bar[LEN];
  int baz[LEN];
  int toto[LEN];
  int ii;
  
  random_uniform_array (-10, 10, foo, LEN);
  random_chunkwise_array (-10, 10, bar, LEN, 10, 100, 'a');
  random_chunkwise_array (-10, 10, baz, LEN, 10, 100, 'd');
  random_chunkwise_array (-10, 10, toto, LEN, 10, 100, 'r');
  
  for (ii = 0; ii < LEN; ++ii)
    printf ("%d\t%d\t%d\t%d\t%d\t%d\n",
	    ii, random_uniform (-10, 10), foo[ii], bar[ii], baz[ii], toto[ii]);
  
  printf ("# plot 'data' u 2 w l t 'rnd'\n"
	  "# plot 'data' u 3 w l t 'rnd'\n"
	  "# plot 'data' u 4 w l t 'asc'\n"
	  "# plot 'data' u 5 w l t 'des'\n"
	  "# plot 'data' u 6 w l t 'mix'\n");
  
  return 0;
}
