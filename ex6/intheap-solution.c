#include <stdio.h>
#include <err.h>
#include <stdlib.h>


#define INTHEAP_CAPACITY  100
#define BUFSIZE  1024


typedef struct {
  int num[INTHEAP_CAPACITY+1]; /* num starts at [1] instead of [0] */
  size_t len;
} IntHeap;


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


void intheap_insert (IntHeap * heap, int num)
{
  if (INTHEAP_CAPACITY <= heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: heap is full", __func__);
  heap->num[++heap->len] = num; /* pre-increment because num starts at [1] */
  
  bubble_up (heap, heap->len);
}


int intheap_extract (IntHeap * heap)
{
  int num;
  
  if (0 == heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: empty heap (violated precondition)", __func__);
  
  num = heap->num[1];		/* remember, we start at [1] instead of [0] */
  heap->num[1] = heap->num[heap->len--];
  
  if (0 < heap->len)
    bubble_down (heap, 1);
  
  return num;
}


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


int main (int argc, char ** argv)
{
  int ii;
  IntHeap heap;
  heap.len = 0;			/* should have an init function */
  
  if (2 > argc) {
    fprintf (stderr,
	     "Please provide a sequence of integer values to put onto the heap.\n"
	     "For example, give the following command:\n"
	     "  %s 1 2 3 1 2 5 4 3\n",
	     argv[0]);
    return 42;
  }
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, __FILE__": argument %d `%s' is not an integer", ii, argv[ii]);
    intheap_insert (&heap, num);
    fprintf (stdout, "inserted %d\n  ", num);
    intheap_dump (&heap, stdout);
  }
  
  fprintf (stdout,"--------------------------------------------------\n");
  while (0 < heap.len) {
    int num = intheap_extract (&heap);
    fprintf (stdout, "extracted %d\n  ", num);
    intheap_dump (&heap, stdout);
  }
  
  return 0;
}
