#include "str-min-heap.h"

/* #include <stdio.h> */
/* #include <err.h> */
/* #include <stdlib.h> */
/* #include <string.h> */


#define CAPACITY  100
#define BUFSIZE  1024


void strheap_new (StrHeap * heap)
{
  memset (heap, 0, sizeof(*heap));
}


void strheap_delete (StrHeap * heap)
{
  for (; heap->len > 0; --heap->len)
    free (heap->str[heap->len]);
  strheap_new (heap);
}


static void strheap_dump_dot (StrHeap * heap, FILE * of, char * label)
{
  int ii;
  fprintf (of, "digraph \"StrHeap\" {\n  graph [label=\"%s\",overlap=scale];\n", label);
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


void strheap_strheap_dump_dot (StrHeap * heap, char * post, char * label)
{
  static char const * pre = "strheap_dump";
  static size_t count = 0;
  FILE * of;
  char buf[BUFSIZE];
  
  if (BUFSIZE <= snprintf (buf, BUFSIZE, "%s-%03lu-%s.dot", pre, count++, post))
    errx (EXIT_FAILURE, "strheap_strheap_dump_dot: insufficient BUFSIZE");
  if (NULL == (of = fopen (buf, "w")))
    err (EXIT_FAILURE, "strheap_strheap_dump_dot: fopen %s", buf);
  
  strheap_dump_dot (heap, of, label);

  if (EOF == fclose (of))
    err (EXIT_FAILURE, "strheap_strheap_dump_dot: fclose %s", buf);
}


static void bubble_up (StrHeap * heap, size_t index)
{
  size_t parent;
  char buf[BUFSIZE];
  
  parent = index / 2;
  while ((parent > 0) && 0 > strcmp (heap->str[index], heap->str[parent])) {
    char * tmp;
    tmp = heap->str[index];
    heap->str[index] = heap->str[parent];
    heap->str[parent] = tmp;
    
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "up %s (index %lu <-> %lu)", tmp, index, parent))
      errx (EXIT_FAILURE, "bubble_up: insufficient BUFSIZE");
    strheap_strheap_dump_dot (heap, "up", buf);
    
    index = parent;
    parent = index / 2;
  }
}


static void bubble_down (StrHeap * heap, size_t index)
{
  size_t left, right, target;
  char buf[BUFSIZE];
  
  target = index;
  for (;;) {
    char * tmp;
    left = 2 * index;
    right = left + 1;
    if (left <= heap->len && 0 > strcmp (heap->str[left], heap->str[target]))
      target = left;
    if (right <= heap->len && 0 > strcmp (heap->str[right], heap->str[target]))
      target = right;
    if (target == index)
      return;
    tmp = heap->str[index];
    heap->str[index] = heap->str[target];
    heap->str[target] = tmp;
    
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "down %s (index %lu <-> %lu)", tmp, index, target))
      errx (EXIT_FAILURE, "bubble_up: insufficient BUFSIZE");
    strheap_strheap_dump_dot (heap, "up", buf);
    
    index = target;
  }
}


void strheap_insert (StrHeap * heap, char * str)
{
  char buf[BUFSIZE];
  
  if (CAPACITY <= heap->len)
    errx (EXIT_FAILURE, "ERROR: heap is full");
  heap->str[++heap->len] = str; /* pre-increment because num starts at [1] */
  
  if (BUFSIZE <= snprintf (buf, BUFSIZE, "strheap_inserted %s (at %lu)", str, heap->len))
    errx (EXIT_FAILURE, "strheap_insert: insufficient BUFSIZE");
  strheap_strheap_dump_dot (heap, "ins", buf);
  
  bubble_up (heap, heap->len);
}


char * strheap_extract (StrHeap * heap)
{
  char * str;
  char buf[BUFSIZE];
  
  if (0 == heap->len)
    errx (EXIT_FAILURE, "ERROR: strheap_extract called on empty heap");
  str = heap->str[1];		/* remember, we start at [1] instead of [0] */
  heap->str[1] = heap->str[heap->len--];
  
  if (0 < heap->len) {
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "strheap_extracted %s (replaced by %s)", str, heap->str[1]))
      errx (EXIT_FAILURE, "strheap_extract: insufficient BUFSIZE");
    strheap_strheap_dump_dot (heap, "strheap_extract", buf);
    
    bubble_down (heap, 1);
  }
  else {
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "strheap_extracted %s (last item)", str))
      errx (EXIT_FAILURE, "strheap_extract: insufficient BUFSIZE");
    strheap_strheap_dump_dot (heap, "strheap_extract", buf);
  }
  
  return str;
}


void strheap_dump (StrHeap * heap, FILE * of)
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
