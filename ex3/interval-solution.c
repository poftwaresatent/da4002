#include <stdio.h>

typedef struct {
  double low, high;
} Interval;


Interval create (double low, double high)
{
  Interval ii;
  ii.low = low;
  ii.high = high;
  return ii;
}


void normalize (Interval * ii)
{
  if (ii->low > ii->high) {
    double tmp = ii->low;
    ii->low = ii->high;
    ii->high = tmp;
  }
}


Interval add (Interval * lhs, Interval * rhs)
{
  normalize (lhs);
  normalize (rhs);
  /*
    NOTE: this is what a careless incorrect solution would look like:
      lhs->low += rhs->low;
      lhs->high += rhs->high;
      return *lhs;
  */
  return create(lhs->low + rhs->low, lhs->high + rhs->high);
}


void print (Interval ii)
{
  printf ("[% 8.2f, % 8.2f]", ii.low, ii.high);
}


int main (int argc, char ** argv)
{
  Interval aa, bb, cc;
  
  aa = create (  3,   2);
  normalize (&aa);
  bb = create ( 50, -10);
  cc = add (&aa, &bb);
  
  printf ("aa = ");
  print (aa);
  printf ("\nbb = ");
  print (bb);
  printf ("\ncc = ");
  print (cc);
  printf ("\n");
  
  return 0;
}
