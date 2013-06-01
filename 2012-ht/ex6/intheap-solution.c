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
  size_t parent;
  
  parent = index / 2;
  while ((parent > 0) && (heap->num[index] > heap->num[parent])) {
    int tmp;
    tmp = heap->num[index];
    heap->num[index] = heap->num[parent];
    heap->num[parent] = tmp;
    
    index = parent;
    parent = index / 2;
  }
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
  size_t left, right, target;
  
  target = index;
  for (;;) {
    int tmp;
    left = 2 * index;
    right = left + 1;
    if (left <= heap->len && heap->num[left] > heap->num[target])
      target = left;
    if (right <= heap->len && heap->num[right] > heap->num[target])
      target = right;
    if (target == index)
      return;
    tmp = heap->num[index];
    heap->num[index] = heap->num[target];
    heap->num[target] = tmp;
    
    index = target;
  }
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
