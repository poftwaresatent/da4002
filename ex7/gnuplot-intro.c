#include <stdio.h>

int main (int argc, char ** argv)
{
  long nn, ii, jj, s1, s2, s3;
  
  for (nn = 100; nn < 5000; nn += 100) {
    s1 = 0;
    s2 = 0;
    s3 = 0;
    for (ii = 0; ii < nn; ++ii) {
      ++s1;
      for (jj = 0; jj < nn; ++jj) {
	++s2;
      }
      for (jj = 1; jj <= nn; jj *= 2) {
	++s3;
      }
    }
    printf ("%ld  %ld  %ld  %ld\n", nn, s1, s2, s3);
  }

  return 0;
}
