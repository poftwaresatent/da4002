#include "graph.h"
#include <err.h>


/*
 * An item for the vertex queue. You can just reuse this...
 */
typedef struct item_s {
  Vertex *vv;
  struct item_s *next;
} Item;

/*
 * Head and tail of the linked list that implements the vertex
 * queue. You can just reuse this...
 */
static Item *head, *tail;


/*
 * Utility function for placing an item at the end of the queue. You
 * can just reuse this...
 */
void enqueue (Vertex *vv)
{
  Item *it;
  if (NULL == (it = calloc (1, sizeof *it)))
    errx (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  it->vv = vv;
  if (NULL == tail) {
    head = it;
    tail = it;
  }
  else {
    tail->next = it;
    tail = it;
  }
}


/*
 * Utility function for retrieving an item from the front of the
 * queue. You can just reuse this...
 */
Vertex * dequeue ()
{
  Vertex *vv;
  Item *tmp;
  if (NULL == head)
    return NULL;
  vv = head->vv;
  tmp = head->next;
  free (head);
  head = tmp;
  if (NULL == tmp)
    tail = NULL;
  return vv;
}


/*
 * Implement this function. You can assume that, before this function
 * gets called, the value of all the vertices is initialized to
 * -1. You will need to mark vertices as visited, which you can do for
 * example by setting their value to 1. And you will need to iterate
 * over all the neighbors of a vertex, for which you can find an
 * example in the test-graph.c source code.
 *
 * You will also need a queue of vertices to visit, for which you can
 * simply use the enqueue() and dequeue() functions defined above.
 */
void bfs (Vertex *vv)
{
  errx (EXIT_FAILURE, "Please implement the breadth-first search function.");
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
  bfs (start);
  
  g_delete (graph);
  return 0;
}
