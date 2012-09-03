#include <stdio.h>

struct complex {
  double re;			/* real part */
  double im;			/* imaginary part */
};

int main (int argc, char ** argv)
{
  struct complex cc;		/* a single complex number */
  struct complex *cptr;		/* a pointer to a complex number */
  struct complex arr[3];	/* an array of three complex numbers */
  struct complex *aptr[3];	/* an array of three pointers to complex numbers */
  int ii;
  
  /* field access on simple variables happens with dot notation */
  cc.re = 1.2;
  cc.im = -0.5;
  
  /* for pointers, fields are accessed via arrow notation */
  cptr = &cc;
  cptr->re *= -0.5;
  cptr->im = 99;
  
  /* for arrays, the index comes first, then the field access */
  for (ii = 0; ii < 3; ++ii) {
    /* value arrays use dot notation */
    arr[ii].re = 0.75 * ii - 1.2;
    arr[ii].im = -0.1;
  }
  
  for (ii = 0; ii < 3; ++ii) {
    aptr[ii] = &arr[2-ii];
  }
  for (ii = 0; ii < 3; ++ii) {
    /* pointer arrays use arrow notation */
    aptr[ii]->re = aptr[ii]->im;
    aptr[ii]->im = 0;
  }
  
  return 0;
}
