#include <stdio.h>

static long sum;

void recursion_a (long nn)
{
  long ii;
  if (nn >= 2) {
    for (ii = 0; ii < nn; ++ii) {
      ++sum;
    }
    recursion_a (nn / 2);
  }
}

void recursion_b (long nn)
{
  long ii;
  if (nn > 1) {
    for (ii = 0; ii < nn; ++ii) {
      ++sum;
    }
    recursion_b (nn - 1);
  }
}

int main (int argc, char ** argv)
{
  long nn, ii, jj, kk;
  
  for (nn = 100; nn <= 7000; nn += 100) {
    
    printf ("%ld", nn);
    fflush (stdout);
    
    /* fragment 1: linear */
    sum = 0;
    for (ii = 0; ii < nn; ++ii) {
      ++sum;
    }
    for (jj = 0; jj < nn; ++jj) {
      ++sum;
    }
    printf ("  %ld", sum);
    fflush (stdout);
    
    /* fragment 2: quadratic */
    sum = 0;
    for (ii = 0; ii < nn; ++ii) {
      for (jj = 0; jj < ii; ++jj) {
	++sum;
      }
    }
    printf ("  %ld", sum);
    fflush (stdout);
    
    /* fragment 3: quintic */
    sum = 0;
    for (ii = 0; ii < nn / 100; ++ii) {
      for (jj = 0; jj < nn * nn / 20000; ++jj) {
	for (kk = 0; kk < jj; ++kk) {
	  ++sum;
	}
      }
    }
    printf ("  %ld", sum);
    fflush (stdout);
    
    /* fragment 4: logarithmic */
    sum = 0;
    for (ii = 1; ii <= nn * nn * nn; ii *= 2) {
      ++sum;
    }
    printf ("  %ld", sum);
    fflush (stdout);
    
    /* fragment 5: N log N */
    sum = 0;
    recursion_a (nn * 10000);
    printf ("  %ld", sum);
    fflush (stdout);
    
    /* fragment 6: cubic */
    sum = 0;
    for (ii = 1; ii <= nn / 100; ++ii) {
      recursion_b (ii);
    }
    printf ("  %ld", sum);
    fflush (stdout);
    
    printf ("\n");
  }

  return 0;
}
