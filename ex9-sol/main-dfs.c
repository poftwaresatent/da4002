#include "graph.h"
#include <err.h>


void dfs (Vertex *vv)
{
  Edge *ee;
  if (vv->value >= 0)
    return;
  printf ("%s\n", vv->name);
  vv->value = 1;
  for (ee = vv->out; ee != NULL; ee = ee->next)
    dfs (ee->dst);
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
  dfs (start);
  
  g_delete (graph);
  return 0;
}
