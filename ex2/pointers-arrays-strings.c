#include <stdio.h>

/*
 * Syntax for pointers and arrays:
 * - &foo is the address where the variable foo is stored
 * - *ptr is the value stored at the address ptr
 * - arr[2] is the third element of an array called arr
 * - arr itself is nothing but a pointer to the first element
 *
 * We also use two more format specifiers for printf:
 * - %p prints an address in hexadecimal
 *      (this is used to show where pointers point)
 * - %s prints a string stored at a certain address.
 *
 * ...and another escape sequence for strings:
 * - \" prints a quote character
 *
 * And we use the fact that the C compiler simply concatenates string
 * literals to split lines to print into separate lines in the
 * sourcecode. This improves readability and reduce the number of calls
 * to printf.
 */

int main(int argc, char ** argv)
{
  int ix, iy;
  int *iptr;
  int ia[3];
  
  double *dptr;
  double da[2];
  
  char *cptr;
  char ca[100];
  
  ix = 99;
  iy = 333;
  printf("Let's start with two integers:\n"
	 "\tix = %d and\n"
	 "\tiy = %d\n",
	 ix, iy);
  
  iptr = &ix;
  printf("ix resides at the address %p\n", iptr);
  iptr = &iy;
  printf("iy resides at the address %p\n", iptr);
  
  printf("\n"
	 "Assigning to ix simply changes ITS value.\n"
	 "\tbefore:\tthe value of ix is %d\n",
	 ix);
  ix = 999;
  printf("\tafter:\tthe value of ix is %d\n", ix);
  
  printf("\n"
	 "Assigning to *iptr changes the value stored AT THAT ADDRESS.\n"
	 "\tbefore:\tthe value at %p is %d\n",
	 iptr, *iptr);
  *iptr = -1111;
  printf("\tafter:\tthe value at %p is %d\n", iptr, *iptr);
  
  printf("\n"
	 "iptr was pointing to iy when we did that, see:\n"
	 "\tiy is now %d\n"
	 "The assignment did not change iptr, it changed iy!\n",
	 iy);
  
  ia[0] = 100;
  ia[1] = 101;
  ia[2] = 102;
  printf("\n"
	 "Let's look at arrays next.\n"
	 "\n"
	 "An array is a block of values of identical type.\n"
	 "Its elements are accessed using an offset within brackets.\n"
	 "\tia contains three values:\n");
  for (ix = 0; ix < 3; ++ix) {
    printf("\t\t ia[%d] = %d\n", ix, ia[ix]);
  }
  
  printf("\n"
	 "An array variable simply points to the beginning of the block.\n"
	 "\tthe array ia starts at address %p\n"
	 "To get at an element, you add offset * typesize to the beginning.\n",
	 ia);
  iptr = ia;
  printf("\tthe value at %p is %d\n", iptr, *iptr);
  iptr = ia + 1;
  printf("\tthe value at %p is %d\n", iptr, *iptr);
  iptr = ia + 2;
  printf("\tthe value at %p is %d\n", iptr, *iptr);

  printf("\n"
	 "The C compiler USUALLY multiplies by the typesize automatically.\n"
	 "\tthe difference between the addresses printed above\n"
	 "\tis the same as sizeof(int), namely %zu\n",
	 sizeof(int));
  
  da[0] = 42.17;
  da[1] = -0.000001;
  dptr = da;
  printf("\n"
	 "Let's try with an array of doubles, and a pointer to double:\n"
	 "\tthe value at %p is %f\n",
	 dptr, *dptr);
  dptr = da + 1;
  printf("\tthe value at %p is %f\n"
	 "\tthe difference between those addresses is %zu\n"
	 "\tnow, dptr points to da[1] so we can change that via *dptr...\n",
	 dptr, *dptr, sizeof(double));
  *dptr = -999.888;
  printf("\tthe value of da[1] is now %f\n", da[1]);
  
  cptr = "hello";
  printf("\n"
	 "Let's look at character strings.\n"
	 "\n"
	 "In C, strings are arrays of char which store ASCII codes.\n"
	 "The end of strings are signalled by placing a zero into the array\n"
	 "\tthe string at %p is \"%s\"\n",
	 cptr, cptr);
  for (ix = 0; ix < 6; ++ix) {
    printf("\tthe ASCII code at %p is %d\n", cptr, *cptr);
    cptr += 1;
  }
  
  ca[0] = 66;
  ca[1] = 121;
  ca[2] = 101;
  ca[3] = 98;
  ca[4] = 121;
  ca[5] = 101;
  ca[6] = 33;
  ca[7] = 0;
  printf("\n"
	 "You can manually assemble strings, too...\n"
	 "\tthe result is: %s\n",
	 ca);
  
  return 0;
}
