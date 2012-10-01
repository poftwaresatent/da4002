#include <stdio.h>
#include <math.h>

int main (int argc, char ** argv)
{
  double T1 = 0.5e-3;
  double T2 = 60;
  size_t N = 100;
  double D = T2 * N * log(N) / T1;
  double precision = 1e-9;
  double x, fx, fpx;
  
  printf ("initial guess: x = %g\n", x);
  for (x = N;;) {
    fx = x * log(x) - D;
    printf ("  f(%g) = %g\n", x, fx);
    if (fabs(fx) <= precision)
      break;
    fpx = log(x) + 1.0;
    x = x - fx / fpx;
  }
  printf ("result: x = %g\n", x);

  printf ("\n"
	  "verify: T2 = %g\n"
	  "        T1 / N / log(N) * x * log(x) = %g\n",
	  T2, T1 / N / log(N) * x * log(x));
  
  return 0;
}
