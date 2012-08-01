/*
  The stdio header provides standard input/output functions. The ones
  we use here are getchar, putchar, and printf.
*/

#include <stdio.h>


/*
  The ctype header provides character type definitions and
  utilities. Here we use the isalnum function to filter the input
  data.
*/

#include <ctype.h>


/*
  This is a simple compile-time constant to allocate a fixed amount of
  data items.
*/

#define MAX_NUMITEMS 1000


/*
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
  

  /*
   * First part: read items and store them in the data array until we
   * either run out of space or the input ends.
   *
   * We also filter the input: only alphanumeric characters get stored
   * in the data array.
   */
  
  /* Remember to initialize the variables! */
  
  numitems = 0;			/* We start with zero items in the data array. */
  item = getchar();		/* The first item is read from standard input. */
  
  /*
    Loop to read items until the end of input. The special constant
    EOF means "end of file" (we read from standard input, which is
    just another file under UNIX).
    
    When you run this program from the terminal, you have to press Ctrl-D in
    order to send EOF. 
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
  
  /* Provide feedback to the user. */
  
  printf ("received %d items:\n  ", numitems);
  for (count = 0; count < numitems; ++count) {
    putchar (data[count]);
  }
  putchar ('\n');
  

  /*
   * Second part: sort the data.
   * 
   * Here we start with a simplistic implementation of an algorthm
   * called bubble sort. The idea is to repeatedly scan the entire
   * data for pairs of adjacent items that are in the wrong
   * order. When such a pair is found, swap its order.
   *
   * To determine how often to scan the array, consider the worst
   * case: if the first element of the array should actually be the
   * last. So, if we have N data items, we have to scan the array N
   * times, because at each scan an item moves at most one position.
   *
   * There are several possibilities for improving this
   * implementation, some of which appear in this exercise. Also,
   * there are many more sorting algorithms, as presented later in the
   * course and studied in the first project.
   */
  
  /*
    Loop to scan the array N times.
  */

  for (count = 0; count < numitems; ++count) {
    
    /*
      Local variable declaration: this index is used inside the loop
      to actually scan the data item by item. Again, here we only
      allocate memory for holding the variable. Can you see where it
      gets initialized?
    */

    int index;
    
    /*
      Inner loop to compare every pair of adjacent items. Notice that
      we start the index at one (instead of zero). After reading the
      rest of the loop, can you explain why this is necessary?
    */

    for (index = 1; index < numitems; ++index) {
      
      /*
	Compare an item with its predecessor. If the predecessor is
	bigger, then we have to swap the two items.
      */

      if (data[index] < data[index - 1]) {

	/* Another local variable: each block can have its own. */
		
	int tmp;
	
	/* Swap the items to correct the order.	*/
	
	tmp = data[index];
	data[index] = data[index - 1];
	data[index - 1] = tmp;
      }
    }
  }
  
  /* Print the result to the terminal. */
  
  printf ("sorted data:\n  ");
  for (count = 0; count < numitems; ++count) {
    putchar (data[count]);
  }
  putchar ('\n');
  

  /*
   * End of program.
   */
  
  /*
    At the end of a successful program run, we return zero to the
    operating system (it is customary to return non-zero values to
    indicate errors).
  */

  return 0;
}
