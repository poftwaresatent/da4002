#include <stdio.h>

int main (int argc, char ** argv)
{
  int ii, jj;
  
  printf ("   ");
  for (ii = 0; ii < 10; ++ii)
    printf ("| %2d ", ii);
  printf ("|\n---+");
  for (ii = 0; ii < 10; ++ii)
    printf ("-----");
  printf ("\n");
  for (ii = 0; ii < 10; ++ii) {
    printf ("%2d |", ii);
    for (jj = 0; jj < 10; ++jj)
      printf (" %2d  ", ii * jj);
    printf ("\n");
  }
  
  return 0;
}
