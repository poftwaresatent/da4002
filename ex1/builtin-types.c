#include <stdio.h>

/*
 * The printf function from the stdio header provides very flexible
 * formatted output of data. Here we use many of its most important
 * format flags:
 * - %d prints an integer
 * - %u prints an unsigned integer
 * - %f prints a floating-point value
 * - %e prints a floating-point value using exponential notation
 * - %c prints a single character
 * - %ld prints a long integer
 * - %lu prints an unsigned long integer
 * - %zu prints an unsigned size (usually, this is the same as %lu)
 *
 * Special characters are specified using so-called escape sequences,
 * which start with a backslash `\'. In this program, we use three
 * escape sequences:
 * - \n finishes the current line and starts a new one
 * - \t inserts a tab
 * - %% writes a single %
 */

int main(int argc, char ** argv)
{
  int aa;
  double bb;
  char cc;
  unsigned long dd;
  unsigned int ee;
  
  aa = 42;
  bb = 17.9;
  cc = 'Q';
  dd = 1234567890123456789;
  
  printf("FORMATTED OUTPUT\n");
  printf("int:\n\t%%d format\t%d\n", aa);
  printf("double:\n\t%%f format\t%f\n", bb);
  printf("\t%%e format\t%e\n", bb);
  printf("char:\n\t%%c format\t%c\n", cc);
  printf("\t%%d format\t%d\n", (int) cc);
  printf("unsigned long:\n\t%%lu format\t%lu\n", dd);
  
  printf("\nMEMORY SIZES\n");
  printf("int:\t%zu bytes\n", sizeof(aa));
  printf("double:\t%zu bytes\n", sizeof(bb));
  printf("char:\t %zu byte\n", sizeof(cc));
  printf("long:\t%zu bytes\n", sizeof(dd));
  
  printf("\nSIGNED and UNSIGNED\n");
  printf("the size does not change:\n\t%zu is %zu\n",
	 sizeof(unsigned long), sizeof(long));
  
  aa = -99;
  ee = aa;
  
  printf("but they are interpreted differently:\n");
  printf("signed:\t\t%d\n", aa);
  printf("unsigned:\t%u\n", ee);
  
  return 0;
}
