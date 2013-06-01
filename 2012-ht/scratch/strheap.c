#include "strheap.h"

/* #include <stdio.h> */
#include <err.h>
#include <stdlib.h>
#include <string.h>


#define BUFSIZE  1024


static const char const * debug_prefix = NULL;


StrHeap * strheap_new ()
{
  StrHeap * heap;
  if (NULL == (heap = calloc (1, sizeof(*heap))))
    err (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  return heap;
}


void strheap_delete (StrHeap * heap)
{
  for (; heap->len > 0; --heap->len)
    free (heap->str[heap->len]);
  strheap_new (heap);
}


static void dump_dot (StrHeap * heap, FILE * of, const char * label)
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


void strheap_dump_dot (StrHeap * heap, const char * pre, const char * post, const char * label)
{
  static size_t count = 0;
  FILE * of;
  char buf[BUFSIZE];
  
  if (BUFSIZE <= snprintf (buf, BUFSIZE, "%s-%03lu-%s.dot", pre, count++, post))
    errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
  if (NULL == (of = fopen (buf, "w")))
    err (EXIT_FAILURE, __FILE__": %s: fopen %s", __func__, buf);
  
  dump_dot (heap, of, label);
  
  if (EOF == fclose (of))
    err (EXIT_FAILURE, __FILE__": %s: fclose %s", __func__, buf);
}


static void bubble_up (StrHeap * heap, size_t index)
{
  size_t parent;
  
  parent = index / 2;
  while ((parent > 0) && 0 > strcmp (heap->str[index], heap->str[parent])) {
    char * tmp;
    tmp = heap->str[index];
    heap->str[index] = heap->str[parent];
    heap->str[parent] = tmp;
    
    if (NULL != debug_prefix) {
      char buf[BUFSIZE];
      if (BUFSIZE <= snprintf (buf, BUFSIZE, "up %s (index %lu <-> %lu)", tmp, index, parent))
	errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
      strheap_dump_dot (heap, debug_prefix, "up", buf);
    }
    
    index = parent;
    parent = index / 2;
  }
}


static void bubble_down (StrHeap * heap, size_t index)
{
  size_t left, right, target;
  
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
    
    if (NULL != debug_prefix) {
      char buf[BUFSIZE];
      if (BUFSIZE <= snprintf (buf, BUFSIZE, "down %s (index %lu <-> %lu)", tmp, index, target))
	errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
      strheap_dump_dot (heap, debug_prefix, "up", buf);
    }
    
    index = target;
  }
}


void strheap_insert (StrHeap * heap, char * str)
{
  if (STRHEAP_CAPACITY <= heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: heap is full", __func__);
  heap->str[++heap->len] = str; /* pre-increment because num starts at [1] */
  
  if (NULL != debug_prefix) {
    char buf[BUFSIZE];
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "inserted %s (at %lu)", str, heap->len))
      errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
    strheap_dump_dot (heap, debug_prefix, "ins", buf);
  }
  
  bubble_up (heap, heap->len);
}


char * strheap_extract (StrHeap * heap)
{
  char * str;
  
  if (0 == heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: empty heap (violated precondition)", __func__);
  
  str = heap->str[1];		/* remember, we start at [1] instead of [0] */
  heap->str[1] = heap->str[heap->len--];
  
  if (0 < heap->len) {
    if (NULL != debug_prefix) {
      char buf[BUFSIZE];
      if (BUFSIZE <= snprintf (buf, BUFSIZE, "extracted %s (replaced by %s)", str, heap->str[1]))
	errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
      strheap_dump_dot (heap, debug_prefix, "ext", buf);
    }
    
    bubble_down (heap, 1);
  }
  else {
    if (NULL != debug_prefix) {
      char buf[BUFSIZE];
      if (BUFSIZE <= snprintf (buf, BUFSIZE, "extracted %s (last item)", str))
	errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
      strheap_dump_dot (heap, debug_prefix, "ext", buf);
    }
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


void strheap_debug_on (void)
{
  debug_prefix = "strheap";
}


void strheap_debug_off (void)
{
  debug_prefix = NULL;
}
