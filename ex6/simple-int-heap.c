#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>


/*
  This simple implementation has a fixed capacity.
*/
#define CAPACITY 1024


typedef struct {
  int num[CAPACITY+1];		/* num starts at [1] instead of [0] */
  size_t len;
} Heap;


void init (Heap * heap)
{
  memset (heap, 0, sizeof(*heap));
}


void bubble_up (Heap * heap, size_t index)
{
  size_t parent = index / 2;
  while ((parent > 0) && (heap->num[index] > heap->num[parent])) {
    int tmp;
    tmp = heap->num[index];
    heap->num[index] = heap->num[parent];
    heap->num[parent] = tmp;
    index = parent;
    parent = index / 2;
  }
}


void bubble_down (Heap * heap, size_t index)
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


void insert (Heap * heap, int num)
{
  if (CAPACITY <= heap->len)
    errx (EXIT_FAILURE, "ERROR: heap is full");
  heap->num[++heap->len] = num; /* pre-increment because num starts at [1] */
  bubble_up (heap, heap->len);
}


int pop (Heap * heap)
{
  int num;
  if (0 == heap->len)
    errx (EXIT_FAILURE, "ERROR: pop called on empty heap");
  num = heap->num[1];		/* remember, we start at [1] instead of [0] */
  heap->num[1] = heap->num[heap->len--];
  bubble_down (heap, 1);
  return num;
}


void dump (Heap * heap)
{
  size_t ii;
  /*
    Yes, I'll say it again: in this case we start the array at index 1
    (one), instead of the usual 0 (zero).
  */
  for (ii = 1; ii <= heap->len; ++ii)
    fprintf (stderr, " %3d", heap->num[ii]);
  fprintf (stderr, "\n");
}


int main (int argc, char ** argv)
{
  int ii;
  Heap heap;
  init (&heap);
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, "failed to parse integer from argument %d `%s'", ii, argv[ii]);
    insert (&heap, num);
    fprintf (stderr, "inserted %d\n  ", num);
    dump (&heap);
  }
  
  printf ("digraph \"Heap\" {\n  graph [label=\"%s", argv[1]);
  for (ii = 2; ii < argc; ++ii)
    printf (" %s", argv[ii]);
  printf ("\",overlap=scale];\n");
  for (ii = 1; ii <= heap.len; ++ii) {
    printf ("  %d [label=\"%d\"];\n", ii, heap.num[ii]);
    if (ii * 2 > heap.len)
      continue;
    printf ("  %d -> %d;\n", ii, ii * 2);
    printf ("  %d -> %d;\n", ii, ii * 2 + 1);
  }
  printf ("}\n");
  
  fprintf (stderr,"--------------------------------------------------\n");
  while (0 < heap.len) {
    int num = pop (&heap);
    fprintf (stderr, "popped %d\n  ", num);
    dump (&heap);
  }

  return 0;
}
