#include <stdio.h>

int main (int argc, char ** argv)
{
  int ii, jj;

  for (ii = 1; ii <= 5; ii++) {
    for (jj = 1; jj <= 5; jj++) {
      printf ("(%d, %d)\n", ii, jj);
    }
  }

  return 0;
}
