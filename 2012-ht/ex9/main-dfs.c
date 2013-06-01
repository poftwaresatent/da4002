#include "graph.h"
#include <err.h>


/*
 * Implement this function. You can assume that, before this function
 * gets called, the value of all the vertices is initialized to
 * -1. You will need to mark vertices as visited, which you can do for
 * example by setting their value to 1. And you will need to iterate
 * over all the neighbors of a vertex, for which you can find an
 * example in the test-graph.c source code.
 */
void dfs (Vertex *vv)
{
  errx (EXIT_FAILURE, "Please implement the depth-first search function.");
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
  dfs (start);
  
  g_delete (graph);
  return 0;
}
