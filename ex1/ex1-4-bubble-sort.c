/*
  The stdio header provides standard input/output functions. The ones
  we use here are getchar, putchar, and printf.
*/
#include <stdio.h>

/*
  The ctype header provides character type definitions and
  utilities. For example the isalnum function which we use here to
  filter the input data.
*/
#include <ctype.h>

/*
  This is a simple compile-time constant to allocate a fixed amount of
  data items.
*/
#define MAX_NUMITEMS 1000


/***************************************************
  Every C program has a main function with exactly this signature. It
  tells the operating system where to start executing the program.
*/
int main (int argc, char ** argv)
{
  /*
    These declarations tell the compiler to allocate memory for three
    single-integer variables and one array of integers. Notice that
    C does NOT automatically initialize these variables for us!
  */
  int item, numitems, count;
  int data[MAX_NUMITEMS];
  
  /***************************************************
    First part: read items and store them in the data array until we
    either run out of space or the input ends. We also ignore filter
    the input, only alphanumeric characters get stored in the data
    array.
  ***************************************************/
  
  /*
    Remember to initialize the variables!
  */
  numitems = 0;			/* We start with zero items in the data array. */
  item = getchar();		/* The first item is read from standard input. */
  
  /*
    Loop to read items until the end of input. The special constant
    EOF means "end of file" (we read from standard input, which is
    just another file under UNIX).
  */
  while (EOF != item) {
    
    if (isalnum(item)) {	/* Is this an alphanumeric character? */
      data[numitems] = item;	/* Store the item. */
      ++numitems;		/* Increase the data size. */
      if (numitems >= MAX_NUMITEMS) { /* Is the data array full? */
	break;
      }
    }
    
    item = getchar();		/* Read the next item from standard input. */
  }
  
  /*
    Provide feedback to the user by printing out the filtered data.
  */
  
  printf ("received %d items:\n  ", numitems);
  for (count = 0; count < numitems; ++count) {
    putchar (data[count]);
  }
  putchar ('\n');
  
  /***************************************************
     Second part: sort the data.

     Here we start with a simplistic implementation of an algorthm
     called bubble sort. The idea behind this algorithms is quite
     simple: repeatedly scan the entire data for pairs of adjacent
     items that are in the wrong order. When such a pair is found,
     swap them.
     
     To determine how often to scan the array, consider the following
     argument.  In the worst case, the first element of the array
     should actually be the last. At each scan, every item moves at
     most one position. So, if we have N data items, we have to scan
     the array N times.
     
     There are several possibilities for making this faster, and there
     are many alternative algorithms for sorting data. Some of them
     appear in this exercise, others will be presented later in the
     course and during the first project.
  ***************************************************/
  
  /*
    Loop to scan the array N times.
  */
  for (count = 0; count < numitems; ++count) {
    
    /*
      Local variable declaration. This index is used inside the loop
      to actually scan the data item by item. Again, here we only
      allocate memory for holding the variable. Can you see where it
      gets initialized?
    */
    int index;
    
    /*
      Inner loop to compare every pair of adjacent items. Notice that
      we start the index at one (instead of zero). Can you explain why
      this is necessary?
    */
    for (index = 1; index < numitems; ++index) {
      
      /*
	Compare an item with its predecessor. If the predecessor is
	bigger, then we have to swap the two items.
      */
      if (data[index] < data[index - 1]) {
	int tmp;		/* Another local variable: each block can have its own. */
	
	/*
	  Swap the items to make the order correct.
	*/
	tmp = data[index];
	data[index] = data[index - 1];
	data[index - 1] = tmp;
      }
    }
  }
  
  /*
    Print the result to the terminal.
  */
  
  printf ("sorted data:\n  ");
  for (count = 0; count < numitems; ++count) {
    putchar (data[count]);
  }
  putchar ('\n');
  
  /***************************************************
    End of program.
  */
  
  /*
    At the end of a successful program run, we return zero to the
    operating system (it is customary to return non-zero values to
    indicate errors).
  */
  return 0;
}
