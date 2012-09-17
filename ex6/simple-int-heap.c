#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>


/*
  This simple implementation has a fixed capacity.
*/
#define CAPACITY  100
#define BUFSIZE  1024


typedef struct {
  int num[CAPACITY+1];		/* num starts at [1] instead of [0] */
  size_t len;
} Heap;


void init (Heap * heap)
{
  memset (heap, 0, sizeof(*heap));
}


void dump_dot (Heap * heap, FILE * of, char * label)
{
  int ii;
  fprintf (of, "digraph \"Heap\" {\n  graph [label=\"%s\",overlap=scale];\n", label);
  for (ii = 1; ii <= heap->len; ++ii) {
    fprintf (of, "  %d [label=\"%d\"];\n", ii, heap->num[ii]);
    if (ii * 2 > heap->len)
      continue;
    fprintf (of, "  %d -> %d;\n", ii, ii * 2);
    if (ii * 2 >= heap->len)
      continue;
    fprintf (of, "  %d -> %d;\n", ii, ii * 2 + 1);
  }
  fprintf (of, "}\n");
}


void dump_dot_file (Heap * heap, char * post, char * label)
{
  static char const * pre = "dump";
  static size_t count = 0;
  FILE * of;
  char buf[BUFSIZE];
  
  if (BUFSIZE <= snprintf (buf, BUFSIZE, "%s-%03lu-%s.dot", pre, count++, post))
    errx (EXIT_FAILURE, "dump_dot_file: insufficient BUFSIZE");
  if (NULL == (of = fopen (buf, "w")))
    err (EXIT_FAILURE, "dump_dot_file: fopen %s", buf);
  
  dump_dot (heap, of, label);

  if (EOF == fclose (of))
    err (EXIT_FAILURE, "dump_dot_file: fclose %s", buf);
}


void bubble_up (Heap * heap, size_t index)
{
  size_t parent;
  char buf[BUFSIZE];
  
  parent = index / 2;
  while ((parent > 0) && (heap->num[index] > heap->num[parent])) {
    int tmp;
    tmp = heap->num[index];
    heap->num[index] = heap->num[parent];
    heap->num[parent] = tmp;
    
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "up %d (index %lu <-> %lu)", tmp, index, parent))
      errx (EXIT_FAILURE, "bubble_up: insufficient BUFSIZE");
    dump_dot_file (heap, "up", buf);
    
    index = parent;
    parent = index / 2;
  }
}


void bubble_down (Heap * heap, size_t index)
{
  size_t left, right, target;
  char buf[BUFSIZE];
  
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
    
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "down %d (index %lu <-> %lu)", tmp, index, target))
      errx (EXIT_FAILURE, "bubble_up: insufficient BUFSIZE");
    dump_dot_file (heap, "up", buf);
    
    index = target;
  }
}


void insert (Heap * heap, int num)
{
  char buf[BUFSIZE];
  
  if (CAPACITY <= heap->len)
    errx (EXIT_FAILURE, "ERROR: heap is full");
  heap->num[++heap->len] = num; /* pre-increment because num starts at [1] */
  
  if (BUFSIZE <= snprintf (buf, BUFSIZE, "inserted %d (at %lu)", num, heap->len))
    errx (EXIT_FAILURE, "insert: insufficient BUFSIZE");
  dump_dot_file (heap, "ins", buf);
  
  bubble_up (heap, heap->len);
}


int pop (Heap * heap)
{
  int num;
  char buf[BUFSIZE];
  
  if (0 == heap->len)
    errx (EXIT_FAILURE, "ERROR: pop called on empty heap");
  num = heap->num[1];		/* remember, we start at [1] instead of [0] */
  heap->num[1] = heap->num[heap->len--];
  
  if (0 < heap->len) {
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "popped %d (replaced by %d)", num, heap->num[1]))
      errx (EXIT_FAILURE, "pop: insufficient BUFSIZE");
    dump_dot_file (heap, "pop", buf);
    
    bubble_down (heap, 1);
  }
  else {
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "popped %d (last item)", num))
      errx (EXIT_FAILURE, "pop: insufficient BUFSIZE");
    dump_dot_file (heap, "pop", buf);
  }
  
  return num;
}


void dump (Heap * heap, FILE * of)
{
  size_t ii;
  /*
    Yes, I'll say it again: in this case we start the array at index 1
    (one), instead of the usual 0 (zero).
  */
  for (ii = 1; ii <= heap->len; ++ii)
    fprintf (of, " %3d", heap->num[ii]);
  fprintf (of, "\n");
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
    dump (&heap, stderr);
  }
  
  dump_dot (&heap, stdout, "FOO");
  
  fprintf (stderr,"--------------------------------------------------\n");
  while (0 < heap.len) {
    int num = pop (&heap);
    fprintf (stderr, "popped %d\n  ", num);
    dump (&heap, stderr);
  }

  return 0;
}
