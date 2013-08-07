#include <stdio.h>

/* print Fahrenheit to Celsius table */
int main (int argc, char **argv)
{
  double fahr, cels;
  fahr = 0;
  while (fahr <= 300) {
    cels = 5 * (fahr - 32) / 9;
    printf ("%f\t%f\n", fahr, cels);
    fahr = fahr + 20;
  }
  return 0;
}
