#include <stdio.h>

long tt (long nn)
{
  if (1 >= nn) {
    return 1;
  }
  return 2 * tt (nn / 2);
}


int main (int argc, char ** argv)
{
  long nn;
  printf ("set key left\n"
	  "plot '-' u 1:2 w lp t 'tt'\n");
  for (nn = 100; nn <= 10000000; nn *= 2) {
    printf ("%ld  %ld\n", nn, tt (nn));
  }
}
