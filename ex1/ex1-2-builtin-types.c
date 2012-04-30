#include <stdio.h>

/*
  The most important format flags used by printf():
  - %d prints an integer
  - %u prints an unsigned integer
  - %f prints a floating-point value
  - %e prints a floating-point value using exponential notation
  - %c prints a single character
  - %ld prints a long integer
  - %lu prints an unsigned long integer
  - %zu prints an unsigned size (usually, this is the same as %lu)
  
  The most important escape sequences:
  - \n finishes the current line and starts a new one
  - \t inserts a tab
  - \\ prints a single backslash
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
  dd = 1234567890L;
  
  printf("values of plain variables:\n");
  printf("  an integer:\t%d\n", aa);
  printf("  a double (using float format):\t%f\n", bb);
  printf("           (using exponential format):\t%e\n", bb);
  printf("  a character:\t%c\n", cc);
  printf("  an unsigned long integer:\t%lu\n", dd);
  
  printf("\nmemory sizes of plain variables:\n");
  printf("  an integer uses %zu bytes.\n", sizeof(aa));
  printf("    passing the type name also works: %zu.\n", sizeof(int));
  printf("  a double uses %zu bytes.\n", sizeof(bb));
  printf("  a character uses %zu byte.\n", sizeof(cc));
  printf("  a long integer uses %zu bytes.\n", sizeof(dd));
  printf("    unsigned or signed does not matter for the size: %zu is %zu\n",
	 sizeof(unsigned long), sizeof(long));
  
  aa = -99;
  ee = aa;
  
  printf("\nsigned and unsigned types are interpreted differently...\n");
  printf("  a signed integer: %d\n", aa);
  printf("  the 'same' but interpreted as unsigned: %u\n", ee);
  
  return 0;
}
