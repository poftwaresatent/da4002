#include <stdio.h>


double power_it (double num, unsigned int exp)
{
  double res;
  if (0 == exp) {
    return 1.0;
  }
  res = num;
  for (; exp > 1; --exp) {
    res *= num;
  }
  return res;
}


double power_rec (double num, unsigned int exp)
{
  if (0 == exp) {
    return 1.0;
  }
  if (1 == exp) {
    return num;
  }
  return num * power_rec (num, exp - 1);
}


int main (int argc, char ** argv)
{
  unsigned int exp;
  double num;
  
  double (*power)(double, unsigned int) = power_rec;
  
  printf ("integer power table\n"
	  " num |");
  for (exp = 0; exp <= 5; ++exp) {
    printf (" %7u |", exp);
  }
  printf ("\n------------------------------------------------------------------\n");
  for (num = 1.0; num <= 5.1; num += 0.2) {
    printf ("%4.1f |", num);
    for (exp = 0; exp <= 5; ++exp) {
      printf (" %7.2f |", power (num, exp));
    }
    printf ("\n");
  }
  
  return 0;
}
