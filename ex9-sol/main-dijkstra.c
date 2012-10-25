#include "graph.h"
#include <err.h>


typedef struct item_s {
  int key;
  Vertex *vv;
} Item;

static Item *heap;
static size_t heaplen;


void enqueue (int key, Vertex *vv)
{
  size_t index, parent;
  ++heaplen;
  heap = realloc (heap, (heaplen+1) * sizeof *heap);
  if (NULL == heap)
    errx (EXIT_FAILURE, __FILE__": %s: realloc", __func__);
  index = heaplen;
  heap[index].key = key;
  heap[index].vv = vv;
  parent = index / 2;
  while ((parent > 0) && (heap[index].key < heap[parent].key)) {
    heap[0] = heap[index];
    heap[index] = heap[parent];
    heap[parent] = heap[0];
    index = parent;
    parent = index / 2;
  }
}


Item dequeue ()
{
  Item it;
  if (0 == heaplen) {
    it.key = -1;
    it.vv = NULL;
    return it;
  }
  it = heap[1];
  if (1 == heaplen) {
    free (heap);
    heap = NULL;
    heaplen = 0;
    return it;
  }
  heap[1] = heap[heaplen];
  heap = realloc (heap, heaplen * sizeof *heap);
  if (NULL == heap)
    errx (EXIT_FAILURE, __FILE__": %s: realloc", __func__);
  --heaplen;
  size_t parent, target, child;
  parent = 1;
  target = 1;
  while (1) {
    child = 2 * parent;
    if (child <= heaplen && heap[child].key < heap[target].key)
      target = child;
    ++child;
    if (child <= heaplen && heap[child].key < heap[target].key)
      target = child;
    if (parent == target)
      break;
    heap[0] = heap[target];
    heap[target] = heap[parent];
    heap[parent] = heap[0];
    parent = target;
  }
  return it;
}


void dumpqueue (const char *foo)
{
  size_t ii;
  printf ("  %s\n", foo);
  if (0 == heaplen) {
    printf ("    EMPTY\n");
    return;
  }
  for (ii = 1; ii <= heaplen; ++ii)
    printf ("    %d %p %s\n", heap[ii].key, heap[ii].vv, heap[ii].vv->name);
}


void dijkstra (Vertex *vv)
{
  vv->value = 0;
  enqueue (0, vv);
  for (;;) {
    Edge *ee;
    Item it = dequeue ();
    if (NULL == it.vv)
      break;
    for (ee = it.vv->out; ee != NULL; ee = ee->next) {
      int key = it.vv->value + ee->cost;
      if ((ee->dst->value < 0) || (ee->dst->value > key)) {
	ee->dst->value = key;
	enqueue (key, ee->dst);
      }
    }
  }
}


int main (int argc, char **argv)
{
  Graph *graph;
  Vertex *start;
  size_t ii;
  
  if (argc < 3)
    errx (EXIT_FAILURE, "Please specify a file name and a city name.");
  graph = g_new ();
  g_load (graph, argv[1]);
  start = g_find (graph, argv[2]);
  if (NULL == start)
    errx (EXIT_FAILURE, "No vertex called %s in file %s", argv[2], argv[1]);
  
  for (ii = 0; ii < graph->size; ++ii)
    graph->vertex[ii]->value = -1;
  dijkstra (start);
  g_print (graph, stderr);
  g_print_dot (graph, stdout);
  
  g_delete (graph);
  return 0;
}
