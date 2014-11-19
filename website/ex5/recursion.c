#include <stdio.h>


/*
 * Just a little helper function for the verbose version of the power
 * function (further down).
 */
void indentation (size_t indent)
{
  for (/**/; 0 < indent; --indent)
    printf ("  ");
}


/*
 * Here is a (silent) recursive implementation of a function which
 * computes the result of an exponentiation.
 */
double power_silent (double base, size_t exponent)
{
  double result;
  if (0 == exponent) {
    result = 0.0;
  }
  else if (1 == exponent) {
    result = base;
  }
  else {
    result = power_silent (base, exponent - 1);
    result *= base;
  }
  return result;
}


/*
 * This is the same function as power_silent, except that it prints a
 * trace of what is going on. It also takes an extra argument called
 * "indent" which just serves the purpose of nicely indenting the
 * messages that are printed as we go through the recursions.
 */
double power_verbose (double base, size_t exponent, size_t indent)
{
  double result;
  
  indentation (indent);
  printf ("BEGIN power_verbose:\n");
  indentation (indent);
  printf ("  base     = %f\n", base);
  indentation (indent);
  printf ("  exponent = %zu\n", exponent);
  
  if (0 == exponent) {
    
    indentation (indent);
    printf ("  done: exponent is zero\n");
    
    result = 0.0;
  }
  else if (1 == exponent) {
    
    indentation (indent);
    printf ("  done: exponent is one\n");
    
    result = base;
  }
  else {
    
    indentation (indent);
    printf ("  more work is needed...\n");
    indentation (indent);
    printf ("  --> recursion!\n");
    
    result = power_verbose (base, exponent - 1, indent + 1);
    
    indentation (indent);
    printf ("  <-- received %f\n", result);
    
    indentation (indent);
    printf ("  just multiply the received number with %f...\n", base);
    
    result *= base;
    
    indentation (indent);
    printf ("  done: the result is %f\n", result);
  }
  
  indentation (indent);
  printf ("RETURN %f\n", result);
  
  return result;
}


/*
 * Finally, this is the way we would normally implement the recursive
 * power function. Notice how compact it is, and that we don't need
 * the result variable.
 */
double power_concise (double base, size_t exponent)
{
  if (0 == exponent)
    return 0.0;
  if (1 == exponent)
    return base;
  return base * power_concise (base, exponent - 1);
}


int main (int argc, char ** argv)
{
  double base = 1.77827941004;
  size_t exponent = 4;
  double result = power_verbose (base, exponent, 0);
  
  printf ("\npower (%f, %zu) = %f\n", base, exponent, result);
  
  return 0;
}
