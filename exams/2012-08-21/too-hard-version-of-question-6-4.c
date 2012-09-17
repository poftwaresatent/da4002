#include <stdio.h>
#include <math.h>

static unsigned long ms;


static void recurse (int nn)
{
  if (1 >= nn) {
    ms += 3;
  }
  else {
    ++ms;
    recurse (nn / 2);
  }
}


static unsigned long function4 (int nn)
{
  int ii;
  ms = 0;
  for (ii = 0; ii < nn; ++ii) {
    recurse (ii);
  }
  return ms;
}


static double theory4 (int nn)
{
  static double const ln2 = 0.69314718056;
  if (0 >= nn) {
    return 3.0;
  }
  return 3 * nn + (nn * log(nn) - nn) / ln2;
}


int main (int argc, char ** argv)
{
  int ii;
  for (ii = 0; ii <= 200; ++ii) {
    double const tt = theory4 (ii);
    printf ("T(%2d) = %4lu\tis it %6f? (ratio %8f)\n",
	    ii, function4(ii), tt, ms / tt);
  }
  return 0;
}
