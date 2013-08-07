#include <stdio.h>


size_t factorial (size_t number)
{
  if (1 >= number)
    return 1;
  return number * factorial (number - 1);
}


int main (int argc, char ** argv)
{
  size_t ii;
  for (ii = 0; ii <= 10; ++ii)
    printf ("%2zu! = %7zu\n", ii, factorial (ii));
  return 0;
}
