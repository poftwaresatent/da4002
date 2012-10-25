#include "graph.h"
#include <err.h>


typedef struct item_s {
  Vertex *vv;
  struct item_s *next;
} Item;

static Item *head, *tail;


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


void bfs (Vertex *vv)
{
  Edge *ee;
  do {
    if (vv->value < 0) {
      printf ("%s\n", vv->name);
      vv->value = 1;
      for (ee = vv->out; ee != NULL; ee = ee->next)
	if (ee->dst->value < 0)
	  enqueue (ee->dst);
    }
    vv = dequeue ();
  } while (NULL != vv);
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
  bfs (start);
  
  g_delete (graph);
  return 0;
}
