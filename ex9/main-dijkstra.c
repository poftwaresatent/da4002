#include "graph.h"
#include <err.h>


/*
 * Items for the priority queue of vertices, needed by Dijkstra's
 * algorithm. You can just reuse this...
*/
typedef struct item_s {
  int key;
  Vertex *vv;
} Item;

/*
 * The priority queue is implemented as a heap, we need to store a
 * pointer to the first element and the number of items on the
 * queue. You can just reuse this...
 */
static Item *heap;
static size_t heaplen;


/*
 * Utility function for placing a vertex on the priority queue. You
 * can just reuse this...
 */
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


/*
 * Utility function for retrieving the item with the smallest key from
 * the vertex priority queue. It always returns an item, but if the
 * queue was empty then the 'vv' field of the returned item will be
 * NULL. You can just reuse this...
 */
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


/*
 * Implement this function. You can assume that, before this function
 * gets called, the value of all the vertices is initialized to
 * -1. You will need a priority queue of vertices to visit, for which
 * you can simply use the enqueue() and dequeue() functions defined
 * above.
 */
void dijkstra (Vertex *vv)
{
  errx (EXIT_FAILURE, "Please implement Dijkstra's algorithm.");
}


/*
 * No need to touch anything here.
 */
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
