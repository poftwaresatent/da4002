#include <stdio.h>
#include <math.h>


void print (double * value)
{
  printf ("  %f\n", *value);
}


void square (double * value)
{
  *value = pow (*value, 2.0);
}


void apply_fct (double * arr, int len, void (*fct)(double*))
{
  for (--len; len > 0; --len)
    fct(arr++);
}


int main (int argc, char ** argv)
{
  double num[10];
  int ii;
  
  for (ii = 0; ii < 10; ++ii)
    num[ii] = ii - 4;
  
  printf ("applying the print function:\n");  
  apply_fct (num, 10, print);

  printf ("\napplying the square function:\n");  
  apply_fct (num, 10, square);
  
  printf ("\napplying the print function again:\n");  
  apply_fct (num, 10, print);
  
  return 0;
}
