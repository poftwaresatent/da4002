#include <stdio.h>

/*
  Syntax for pointers and arrays:
  - &foo is the address where the variable foo is stored
  - *ptr is the value stored at the address ptr
  - arr[2] is the third element of an array called arr
  - arr itself is nothing but a pointer to the first element
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
  printf("here are two integers:\n\tix = %d and\n\tiy = %d\n", ix, iy);
  
  iptr = &ix;
  printf("ix is stored at the address %p\n", iptr);
  iptr = &iy;
  printf("iy is stored at the address %p\n", iptr);
  
  printf("\nassigning to ix simply changes ITS value.\n");
  printf("\tbefore:\tthe value of ix is %d\n", ix);
  ix = 999;
  printf("\tafter:\tthe value of ix is %d\n", ix);
  
  printf("\nassigning to *iptr changes the value stored AT THAT ADDRESS.\n");
  printf("\tbefore:\tthe value at %p is %d\n", iptr, *iptr);
  *iptr = -1111;
  printf("\tafter:\tthe value at %p is %d\n", iptr, *iptr);
  
  printf("\niptr was pointing to iy when we did that, see:\n");
  printf("\tiy is now %d\n", iy);
  printf("the assignment did not change iptr, it changed iy!\n");
  
  ia[0] = 100;
  ia[1] = 101;
  ia[2] = 102;
  printf("\nan array is a block of values of identical type.\n");
  printf("its elements are accessed using an offset within brackets.\n");
  printf("\tia contains three values:\n");
  printf("\t\t ia[0] = %d\n", ia[0]);
  printf("\t\t ia[1] = %d\n", ia[1]);
  printf("\t\t ia[2] = %d\n", ia[2]);
  
  printf("\nan array variable simply points to the beginning of the block.\n");
  printf("\tthe array ia starts at address %p\n", ia);
  printf("to get an element, you add offset times size to the beginning.\n");
  iptr = ia;
  printf("\tthe value at %p is %d\n", iptr, *iptr);
  iptr = ia + 1;
  printf("\tthe value at %p is %d\n", iptr, *iptr);
  iptr = ia + 2;
  printf("\tthe value at %p is %d\n", iptr, *iptr);
  
  printf("\nthe C compiler USUALLY multiplies by the size automatically.\n");
  printf("\tthe difference between the addresses printed above...\n");
  printf("\t...is the same as sizeof(int) which is %zu\n", sizeof(int));
  
  printf("\nlet's try with an array of doubles, and a pointer to double:\n");
  da[0] = 42.17;
  da[1] = -0.000001;
  dptr = da;
  printf("\tthe value at %p is %f\n", dptr, *dptr);
  dptr = da + 1;
  printf("\tthe value at %p is %f\n", dptr, *dptr);
  printf("\tthe difference between those addresses is %zu\n", sizeof(double));
  printf("\tnow, dptr points to da[1] so we can change that via *dptr...\n");
  *dptr = -999.888;
  printf("\tthe value of da[1] is now %f\n", da[1]);
  
  printf("\nin C, strings are arrays of char which store ASCII codes.\n");
  printf("string ends are signalled by placing a zero into the array\n");
  cptr = "hello";
  printf("\tthe string at %p is %s\n", cptr, cptr);
  printf("\tthe ASCII code at %p is %d\n", cptr, *cptr);
  cptr += 1;
  printf("\tthe ASCII code at %p is %d\n", cptr, *cptr);
  cptr += 1;
  printf("\tthe ASCII code at %p is %d\n", cptr, *cptr);
  cptr += 1;
  printf("\tthe ASCII code at %p is %d\n", cptr, *cptr);
  cptr += 1;
  printf("\tthe ASCII code at %p is %d\n", cptr, *cptr);
  cptr += 1;
  printf("\tthe ASCII code at %p is %d\n", cptr, *cptr);
  
  printf("\nyou can manually assemble strings, too...\n");
  ca[0] = 66;
  ca[1] = 121;
  ca[2] = 101;
  ca[3] = 98;
  ca[4] = 121;
  ca[5] = 101;
  ca[6] = 33;
  ca[7] = 0;
  printf("\tthe result is: %s\n", ca);
  
  return 0;
}
