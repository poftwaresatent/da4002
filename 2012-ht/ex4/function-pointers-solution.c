#include <stdio.h>
#include <math.h>


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


void product (double *lhs, double *rhs)
{
  *lhs = *lhs * *rhs;
}


/*
 * A function that looks weird at first, but does something quite
 * powerful: it receives an array of doubles, and applies a function
 * to each number in that array. However, the function which is
 * applied is not determined here, it is defined by the location where
 * we call apply_fct. This is achieved using a function pointer.
 *
 * Function pointers seem confusing at first, but they really are very
 * simple once you realize that a function is nothing else but an
 * address! In fact, when you make a function call, execution will
 * jump to that address, and then back again when the function
 * returns.
 *
 * The only thing that is strange about function pointers is the
 * syntax required to declare them:
 *  1. the return type, just like when declaring a function
 *  2. an opening parenthesis followed by a star
 *  3. the name under which this function pointer should be made available
 *  4. a closing parenthesis
 *  5. another opening perenthesis
 *  6. the argument list, but it is common to just list the types and omit the argument names
 *  7. a final closing parenthesis
 *
 * So, when we write "void (*fct)(double*)" (see the last argument
 * below) this gets interpreted as:
 *  - fct is a function pointer: it stores the address of a function
 *  - the function returns void (in other words: nothing)
 *  - the function takes a single double* as argument
 *
 * In the body of apply_fct, we can now use the string "fct" just like
 * a regular function call. But it can call any function that matches
 * the declaration. In this case, any function that takes a double*
 * and returns nothing. Which function gets called depends on what
 * gets passed as third argument into apply_fct (see the three
 * examples in the main function).
 */
void apply_fct (double * arr, int len, void (*fct)(double*))
{
  for (; len > 0; --len)
    fct(arr++);
}


void apply_fct2 (double * arr, int len, void (*fct)(double*, double*))
{
  double * next = arr + 1;
  for (--len; len > 0; --len)
    fct(arr++, next++);
}


int main (int argc, char ** argv)
{
  double num[10];
  int ii;
  
  /*
    fct is a function pointer, the declaration follows the same
    principle as for the third argument of of apply_fct
  */
  void (*fct)(double*);
  
  for (ii = 0; ii < 10; ++ii)
    num[ii] = ii - 4;
  
  /*
    In order to get the address of a function, we simply write the
    function name without any parenthesis.
  */
  printf ("applying the print function:\n");  
  apply_fct (num, 10, print);
  
  /*
    As you can see, the apply_fct uses whatever function we give it
    and passes every item in the num array to it.
  */
  printf ("\napplying the square function:\n");  
  apply_fct (num, 10, square);
  
  /*
    We can just as easily store the address of a function in a
    variable. NOTICE that there is no "&"!
  */
  printf ("\napplying the print function, using an explicit pointer variable:\n");
  fct = print;
  apply_fct (num, 10, fct);
  
  apply_fct2 (num, 10, product);
  printf ("\nafter the product function:\n");  
  apply_fct (num, 10, print);
  
  return 0;
}
