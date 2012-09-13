#include <stdio.h>
#include <math.h>


/*
 * A typedef for function pointers looks the same as a function
 * pointer declaration, but now the name after "(*" defines a new
 * type.  After this definition, we can use "fct_t" instead of the
 * much more cumbersome "void (*fct)(double*)" later on. It is
 * customary to write typedefs for your function pointer types, even
 * if you don't use them more than once, just to make the code more
 * readable.
 */
typedef void (*fct_t)(double*);


/*
 * A simple function that takes a pointer and prints the number that
 * is being pointed to.
 */
void print (double * value)
{
  printf ("  %f\n", *value);
}


/*
 * A simple function that overwrites a number with its square.
 */
void square (double * value)
{
  *value = pow (*value, 2.0);
}


/*
 * A simple function that overwrites a number with the square root of
 * its absolute value
 */
void rootabs (double * value)
{
  *value = sqrt(fabs(*value));
}


/*
 * This function is almost the same as before, but now it takes an
 * array of function pointers and will apply each value in the array
 * to each function in functab. In order to make the declaration of
 * functab more readable, we introduced a typedef at the top of this
 * file.
 */
void apply_fct (double * arr, int arrlen, fct_t * functab, int functablen)
{
  for (; arrlen > 0; --arrlen) {
    int ii;
    for (ii = 0; ii < functablen; ++ii)
      functab[ii](arr);
    ++arr;
  }
}


int main (int argc, char ** argv)
{
  double num[10];
  int ii;
  
  /*
    fct is now an array of function pointers
  */
  fct_t fct[] = {
    print,
    square,
    print,
    rootabs,
    print
  };
  int fctlen = sizeof(fct) / sizeof(*fct);
  
  for (ii = 0; ii < 10; ++ii)
    num[ii] = ii - 4;
  
  apply_fct (num, 10, fct, fctlen);
  
  return 0;
}
