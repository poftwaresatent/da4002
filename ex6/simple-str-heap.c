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
  char * str[CAPACITY+1];	/* num starts at [1] instead of [0] */
  size_t len;
} Heap;


void init (Heap * heap)
{
  memset (heap, 0, sizeof(*heap));
}


void delete (Heap * heap)
{
  for (; heap->len > 0; --heap->len)
    free (heap->str[heap->len]);
  init (heap);
}


void dump_dot (Heap * heap, FILE * of, char * label)
{
  int ii;
  fprintf (of, "digraph \"Heap\" {\n  graph [label=\"%s\",overlap=scale];\n", label);
  for (ii = 1; ii <= heap->len; ++ii) {
    fprintf (of, "  %d [label=\"%s\"];\n", ii, heap->str[ii]);
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
  while ((parent > 0) && 0 < strcmp (heap->str[index], heap->str[parent])) {
    char * tmp;
    tmp = heap->str[index];
    heap->str[index] = heap->str[parent];
    heap->str[parent] = tmp;
    
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "up %s (index %lu <-> %lu)", tmp, index, parent))
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
    char * tmp;
    left = 2 * index;
    right = left + 1;
    if (left <= heap->len && 0 < strcmp (heap->str[left], heap->str[target]))
      target = left;
    if (right <= heap->len && 0 < strcmp (heap->str[right], heap->str[target]))
      target = right;
    if (target == index)
      return;
    tmp = heap->str[index];
    heap->str[index] = heap->str[target];
    heap->str[target] = tmp;
    
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "down %s (index %lu <-> %lu)", tmp, index, target))
      errx (EXIT_FAILURE, "bubble_up: insufficient BUFSIZE");
    dump_dot_file (heap, "up", buf);
    
    index = target;
  }
}


void insert (Heap * heap, char * str)
{
  char buf[BUFSIZE];
  
  if (CAPACITY <= heap->len)
    errx (EXIT_FAILURE, "ERROR: heap is full");
  heap->str[++heap->len] = str; /* pre-increment because num starts at [1] */
  
  if (BUFSIZE <= snprintf (buf, BUFSIZE, "inserted %s (at %lu)", str, heap->len))
    errx (EXIT_FAILURE, "insert: insufficient BUFSIZE");
  dump_dot_file (heap, "ins", buf);
  
  bubble_up (heap, heap->len);
}


char * extract (Heap * heap)
{
  char * str;
  char buf[BUFSIZE];
  
  if (0 == heap->len)
    errx (EXIT_FAILURE, "ERROR: extract called on empty heap");
  str = heap->str[1];		/* remember, we start at [1] instead of [0] */
  heap->str[1] = heap->str[heap->len--];
  
  if (0 < heap->len) {
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "extracted %s (replaced by %s)", str, heap->str[1]))
      errx (EXIT_FAILURE, "extract: insufficient BUFSIZE");
    dump_dot_file (heap, "extract", buf);
    
    bubble_down (heap, 1);
  }
  else {
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "extracted %s (last item)", str))
      errx (EXIT_FAILURE, "extract: insufficient BUFSIZE");
    dump_dot_file (heap, "extract", buf);
  }
  
  return str;
}


void dump (Heap * heap, FILE * of)
{
  size_t ii;
  /*
    Yes, I'll say it again: in this case we start the array at index 1
    (one), instead of the usual 0 (zero).
  */
  for (ii = 1; ii <= heap->len; ++ii)
    fprintf (of, " %s", heap->str[ii]);
  fprintf (of, "\n");
}


int main (int argc, char ** argv)
{
  int ii;
  Heap heap;
  init (&heap);
  
  for (ii = 1; ii < argc; ++ii) {
    char * str;
    if (NULL == (str = strdup (argv[ii])))
      err (EXIT_FAILURE, "strdup failed on argument %d `%s'", ii, argv[ii]);
    insert (&heap, str);
    fprintf (stderr, "inserted %s\n  ", str);
    dump (&heap, stderr);
  }
  
  fprintf (stderr,"--------------------------------------------------\n");
  while (0 < heap.len) {
    char * str = extract (&heap);
    fprintf (stderr, "extracted %s\n  ", str);
    dump (&heap, stderr);
    free (str);
  }
  
  return 0;
}
