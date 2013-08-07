#include <stdio.h>

int main (int argc, char ** argv)
{
  int ai = 42117039;
  float af = ai;
  double ad = ai;
  unsigned char * cp;
  int ii;
  
  printf ("the number %d can be stored as:\n  an int\n    size: %zu bytes\n    values:", ai, sizeof(int));
  cp = (unsigned char*) &ai;
  for (ii = 0; ii < sizeof(ai); ++ii)
    printf (" %02x", cp[ii]);
  
  printf ("\n  a float\n    size: %zu bytes\n    values:", sizeof(float));
  cp = (unsigned char*) &af;
  for (ii = 0; ii < sizeof(af); ++ii)
    printf (" %02x", cp[ii]);
  
  printf ("\n  a double\n    size: %zu bytes\n    values:", sizeof(double));
  cp = (unsigned char*) &ad;
  for (ii = 0; ii < sizeof(ad); ++ii)
    printf (" %02x", cp[ii]);
  printf ("\n");
  
  return 0;
}
