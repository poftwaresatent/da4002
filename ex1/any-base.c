#include <stdio.h>

int main (int argc, char ** argv)
{
  unsigned short number = -1;//6245;
  unsigned short base = 2;//3;
  unsigned short factor = 1;
  
  printf ("%u is the sum of:\n", number);
  while (number >= base) {
    printf ("  %u * %5u\n", number % base, factor);
    number /= base;
    factor *= base;
  }
  printf ("  %u * %u\n", number, factor);
  
  return 0;
}
