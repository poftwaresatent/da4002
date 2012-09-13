#include <stdio.h>


int main (int argc, char ** argv)
{
  int aa, bb, cc;
  double xx, yy, zz;
  char *foo;
  void *ptr1, *ptr2;
  
  aa = 42;
  bb = 17;
  xx = 42.0;
  yy = 17.0;
  foo = "forty-two";
  
  /*
   * Basic idea: a void* can store an int*, but that "forgets" the
   * type information. So, in order to get the value back, we need to
   * explicitly tell the compiler that we need an int.
   */
  ptr1 = &aa;
  printf ("address of aa: %p\n",
	  ptr1);
  printf ("value of aa, directly:     %d\n",
	  aa);
  printf ("value of aa, through ptr1: %d (of course the same, but the code needs a cast)\n",
	  /*
	    The next line is tricky to read the first time you see
	    such a thing. It's best to go from right to left:
	    
	    - ptr1 is a void*
              which means: an address to some value of unspecified type
	      
	    - (int*) is a cast
	      this one means: reinterpret the void* to be an int*
	      in other words: (int*)ptr1 points to an int value
	      
	    - * is the de-referencing operator
	      which means: take the value stored at an address
	      in this case, due to the cast, it knows the value is an int
	      
	    Notice that "(int)*ptr1" would not work, because *ptr1 has
	    type void, which can never be used (it essentially means
	    "nothing").
	  */
	  * (int*) ptr1);
  
  /*
   * The same basic idea works for any type, such as double.
   */
  ptr1 = &xx;
  printf ("\naddress of xx: %p\n",
	  ptr1);
  printf ("value of xx, directly:     %f\n",
	  xx);
  printf ("value of xx, through ptr1: %f (again the same, but with a cast)\n",
	  *(double*)ptr1);
  
  /*
   * It even works for pointer types, such as char*. Note that here,
   * &foo has type char** (two stars), but we store it in a void*
   * (just one star). But a char** is still just a pointer, so a void*
   * can hold it.
   */
  ptr1 = &foo;
  printf ("\naddress of foo: %p\n",
	  ptr1);
  printf ("value of foo, directly:     %s\n",
	  foo);
  printf ("value of foo, through ptr1: %s (this time the cast looks even weirder)\n",
	  *(char**)ptr1);
  
  /*
   * So, the nice thing about void* is that they can store an address
   * of anything. The bad thing about them is that you have to
   * manually cast them to the correct type when you use them. And
   * this can cause surprises when you get that wrong, as illustrated
   * below.
   */
  
  /*
    Let's add two numbers via generic pointers. And let's do it right,
    and then wrong, just to show the effect.
  */
  
  ptr1 = &aa;
  ptr2 = &bb;
  cc = *(int*)ptr1 + *(int*)ptr2;
  printf ("\nthe sum of aa and bb is %d\n", cc);
  
  ptr1 = &xx;
  ptr2 = &yy;
  cc = *(int*)ptr1 + *(int*)ptr2;
  printf ("oops: we though we had ints, but they were doubles...\n"
	  "  and the sum seems to be %d\n", cc);  
  
  zz = *(double*)ptr1 + *(double*)ptr2;
  printf ("\nusing the corect cast fixes that:\n"
	  "  the sum of xx and yy is %f\n", zz);

  ptr1 = &aa;
  ptr2 = &bb;
  zz = *(double*)ptr1 + *(double*)ptr2;
  printf ("oops the other way around: we have ints but interpret them as doubles:\n"
	  "  the sum seems to be %f\n", zz);
  
  /*
    A final point: here we know that the pointers point to ints, and
    ints can be converted to doubles IF YOU TELL THE COMPILER the
    correct types.
  */
  zz = *(int*)ptr1 + *(int*)ptr2;
  printf ("\nusing the corect casts again fixes the problem:\n"
	  "  the sum of aa and bb stored in a double is %f\n", zz);
  
  return 0;
}
