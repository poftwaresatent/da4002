#include <stdio.h>


size_t factorial (size_t number)
{
  /*
   * Implement the factorial function based on the following:
   *  1. factorial (0) is 1
   *  2. factorial (1) is 1
   *  3. factorial (N) is N * factorial (N-1)
   *  
   * Hint: the first two facts result in termination conditions, where
   * you can directly return a value. The third fact requires a
   * recursion, and then returning a value based on the recursion
   * result and something else...
  */
  return 0;
}


int main (int argc, char ** argv)
{
  size_t ii;
  for (ii = 0; ii <= 10; ++ii)
    printf ("%2zu! = %7zu\n", ii, factorial (ii));
  return 0;
}
