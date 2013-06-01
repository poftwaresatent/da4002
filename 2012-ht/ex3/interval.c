#include <stdio.h>

typedef struct {
  int low, high;
} Interval;


Interval create (int low, int high)
{
  Interval ii;
  ii.low = low;
  ii.high = high;
  return ii;
}


Interval add (Interval lhs, Interval rhs)
{
  lhs.low += rhs.low;
  lhs.high += rhs.high;
  return lhs;
}


void print (Interval ii)
{
  printf ("[% 4d, % 4d]", ii.low, ii.high);
}


int main (int argc, char ** argv)
{
  Interval aa, bb, cc;
  
  aa = create ( 2,   3);
  bb = create (-10, 50);
  cc = add (aa, bb);
  
  printf ("aa = ");
  print (aa);
  printf ("\nbb = ");
  print (bb);
  printf ("\ncc = ");
  print (cc);
  printf ("\n");
  
  return 0;
}
