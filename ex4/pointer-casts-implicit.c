#include <stdio.h>


int sum_of_int (int * aa, int * bb)
{
  return *aa + *bb;
}


double sum_of_double (double * xx, double * yy)
{
  return *xx + *yy;
}


int main (int argc, char ** argv)
{
  int aa, bb;
  double xx, yy;
  void *ptr1, *ptr2;
  
  aa = 42;
  bb = 17;
  xx = 42.0;
  yy = 17.0;
  
  /*
   * The nice thing about passing void* to functions that expect some
   * other type of pointer is that C will automatically perform the
   * cast for you. The bad thing about this is that your code becomes
   * less epxlicit about the types involved, which makes it harder for
   * human minds to find bugs when they are related to those implicit
   * casts.
   */
  
  ptr1 = &aa;
  ptr2 = &bb;
  printf ("sum_of_int using correct pointers:      %d\n",
	  /*
	    IMPORTANT to notice: there is no need to say (int*)ptr1
	  */
	  sum_of_int(ptr1, ptr2));
  
  ptr1 = &xx;
  ptr2 = &yy;
  printf ("sum_of_int using incorrect pointers:    %d\n",
	  sum_of_int(ptr1, ptr2));
  
  printf ("sum_of_double using correct pointers:   %f\n",
	  sum_of_double(ptr1, ptr2));
  
  ptr1 = &aa;
  ptr2 = &bb;
  printf ("sum_of_double using incorrect pointers: %f\n",
	  sum_of_double(ptr1, ptr2));
  
  return 0;
}
