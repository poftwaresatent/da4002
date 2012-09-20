#include "intheap.h"

#include <err.h>
#include <stdlib.h>
/* #include <string.h> */


#define BUFSIZE  1024


static const char const * debug_prefix = NULL;


IntHeap * intheap_new ()
{
  IntHeap * heap;
  if (NULL == (heap = calloc (1, sizeof(*heap))))
    err (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  return heap;
}


void intheap_delete (IntHeap * heap)
{
#error this looks really wrong
  intheap_new (heap);
}


static void dump_dot (IntHeap * heap, FILE * of, const char * label)
{
  int ii;
  fprintf (of, "digraph \"IntHeap\" {\n  graph [label=\"%s\",overlap=scale];\n", label);
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


void intheap_dump_dot (IntHeap * heap, const char * pre, const char * post, const char * label)
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


static void bubble_up (IntHeap * heap, size_t index)
{
  size_t parent;
  
  parent = index / 2;
  while ((parent > 0) && (heap->num[index] > heap->num[parent])) {
    int tmp;
    tmp = heap->num[index];
    heap->num[index] = heap->num[parent];
    heap->num[parent] = tmp;
    
    if (NULL != debug_prefix) {
      char buf[BUFSIZE];
      if (BUFSIZE <= snprintf (buf, BUFSIZE, "up %d (index %lu <-> %lu)", tmp, index, parent))
	errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
      intheap_dump_dot (heap, debug_prefix, "up", buf);
    }
    
    index = parent;
    parent = index / 2;
  }
}


static void bubble_down (IntHeap * heap, size_t index)
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
    
    if (NULL != debug_prefix) {
      char buf[BUFSIZE];
      if (BUFSIZE <= snprintf (buf, BUFSIZE, "down %d (index %lu <-> %lu)", tmp, index, target))
	errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
      intheap_dump_dot (heap, debug_prefix, "up", buf);
    }
    
    index = target;
  }
}


void intheap_insert (IntHeap * heap, int num)
{
  if (INTHEAP_CAPACITY <= heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: heap is full", __func__);
  heap->num[++heap->len] = num; /* pre-increment because num starts at [1] */
  
  if (NULL != debug_prefix) {
    char buf[BUFSIZE];
    if (BUFSIZE <= snprintf (buf, BUFSIZE, "inserted %d (at %lu)", num, heap->len))
      errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
    intheap_dump_dot (heap, debug_prefix, "ins", buf);
  }
  
  bubble_up (heap, heap->len);
}


int intheap_extract (IntHeap * heap)
{
  int num;
  
  if (0 == heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: empty heap (violated precondition)", __func__);
  
  num = heap->num[1];		/* remember, we start at [1] instead of [0] */
  heap->num[1] = heap->num[heap->len--];
  
  if (0 < heap->len) {
    if (NULL != debug_prefix) {
      char buf[BUFSIZE];
      if (BUFSIZE <= snprintf (buf, BUFSIZE, "extracted %d (replaced by %d)", num, heap->num[1]))
	errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
      intheap_dump_dot (heap, debug_prefix, "ext", buf);
    }
    
    bubble_down (heap, 1);
  }
  else {
    if (NULL != debug_prefix) {
      char buf[BUFSIZE];
      if (BUFSIZE <= snprintf (buf, BUFSIZE, "extracted %d (last item)", num))
	errx (EXIT_FAILURE, __FILE__": %s: insufficient BUFSIZE", __func__);
      intheap_dump_dot (heap, debug_prefix, "ext", buf);
    }
  }
  
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


void intheap_debug_on (void)
{
  debug_prefix = "intheap";
}


void intheap_debug_off (void)
{
  debug_prefix = NULL;
}
