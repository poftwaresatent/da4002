#include <stdio.h>

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
    recurse (nn);
  }
  return ms;
}


int main (int argc, char ** argv)
{
  int ii;
  for (ii = 0; ii <= 20; ++ii) {
    printf ("T(%2d) = %lu\n", ii, function4(ii));
  }
  return 0;
}
