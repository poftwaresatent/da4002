#include <stdio.h>
#include <err.h>
#include <stdlib.h>


#define INTHEAP_CAPACITY  100
#define BUFSIZE  1024


typedef struct {
  int num[INTHEAP_CAPACITY+1]; /* num starts at [1] instead of [0] */
  size_t len;
} IntHeap;


/*
 * **************************************************
 * * IMPLEMENT THIS FUNCTION ************************
 * **************************************************
 */
void bubble_up (IntHeap * heap, size_t index)
{
  /*
    The purpose of this function is to "bubble up" the value which is
    stored at heap->num[index] by repeatedly swapping it with its
    parent, until the heap property is respected.
    
    Hints:
    - The parent for a given index is simply index/2
    - The heap property means that heap->num[parent] is bigger (or
      equal) to heap->num[index]
      
    BE CAREFUL about the fact the the first element of the heap (the
    "root") is stored at heap->num[1]. This is different from the
    normal way of using arrays, where the first element would be
    stored at num[0].
  */
  printf ("*** Please implement bubble_up.\n");
}


/*
 * Function to insert a number into the heap. You don't need to change
 * this, but read it in order to understand why bubble_up is needed.
 */
void intheap_insert (IntHeap * heap, int num)
{
  if (INTHEAP_CAPACITY <= heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: heap is full", __func__);
  
  /*
    pre-increment because num index starts at [1] instead of [0]
  */
  heap->num[++heap->len] = num;
  
  bubble_up (heap, heap->len);
}


/*
 * **************************************************
 * * IMPLEMENT THIS FUNCTION ************************
 * **************************************************
 */
void bubble_down (IntHeap * heap, size_t index)
{
  /*
    The purpose of this function is to "bubble down" the value which
    is at heap->num[index] by repeatedly swapping it with one of its
    children, until the heap property is restored. If both the left
    and the right child violate the heap property, then you should
    swap with the one that's worse (that is to say: the one with the
    highest value).
    
    Hints:
    - The left child of a given index is simply 2*index.
    - The right child is at 2*index+1;
    - The heap property means the same as before, of course.
  */
  printf ("*** Please implement bubble_down.\n");
}


/*
 * Function to extract the maximum number from the heap. You don't
 * need to change anything here, but read it in order to see why
 * bubble_down is needed.
 */
int intheap_extract (IntHeap * heap)
{
  int num;
  
  if (0 == heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: empty heap (violated precondition)", __func__);
  
  /*
    remember, we start at [1] instead of [0]
  */
  num = heap->num[1];
  heap->num[1] = heap->num[heap->len--];
  
  if (0 < heap->len)
    bubble_down (heap, 1);
  
  return num;
}


/*
 * Function to write the heap contents to the terminal. No need to
 * change anything here.
 */
void intheap_dump (IntHeap * heap, FILE * of)
{
  size_t ii;
  /*
    Yes, I'll say it again: in this case we start the array at index 1
    (one), instead of the usual 0 (zero).
  */
  for (ii = 1; ii <= heap->len; ++ii)
    fprintf (of, " %d", heap->num[ii]);
  fprintf (of, "\n");
}


/*
 * The main function does not need to be changed, either. It reads
 * numbers from the command line and inserts them one after the other
 * into a heap. The heap contents are printed after each
 * insertion. Then, the maximum number is repeatedly extracted from
 * the heap, until it is empty. Each time, the heap contents are again
 * written out.
 */
int main (int argc, char ** argv)
{
  int ii;
  IntHeap heap;
  
  /*
    Initialize the heap.
  */
  heap.len = 0;
  
  /*
    Check if we got called with any command-line arguments.
  */
  if (2 > argc) {
    fprintf (stderr,
	     "Please provide a sequence of integer values to put onto the heap.\n"
	     "For example, give the following command:\n"
	     "  %s 1 2 3 1 2 5 4 3\n",
	     argv[0]);
    return 42;
  }
  
  /*
    Read number from the command line, inserting each one into the
    heap.
   */
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, __FILE__": argument %d `%s' is not an integer", ii, argv[ii]);
    intheap_insert (&heap, num);
    fprintf (stdout, "inserted %d\n  ", num);
    intheap_dump (&heap, stdout);
  }
  
  fprintf (stdout,"--------------------------------------------------\n");

  /*
    Repeatedly extract the maximum number until the heap is empty.
  */
  
  while (0 < heap.len) {
    int num = intheap_extract (&heap);
    fprintf (stdout, "extracted %d\n  ", num);
    intheap_dump (&heap, stdout);
  }
  
  return 0;
}
