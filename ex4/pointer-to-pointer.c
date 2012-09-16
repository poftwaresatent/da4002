#include <stdio.h>

int getptr (int guess, double ** data)
{
  static double value = 42.0;
  if (42 != guess)
    return -1;
  *data = &value;
  return 0;
}

int main (int argc, char ** argv)
{
  double * ptr;
  int guess = 42;
  if (0 == getptr (guess, &ptr))
    printf ("guess = %d   pointer = %p   value = %f\n", guess, ptr, *ptr);
  else
    printf ("it's not at %d...\n", guess);
  return 0;
}
