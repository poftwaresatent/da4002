#include "graph.h"

int main (int argc, char **argv)
{
  Graph *graph;
  int ii;
  
  graph = g_new ();
  if (argc > 1)
    g_load (graph, argv[1]);
  else
    g_parse (graph, stdin);
  
  for (ii = 0; ii < graph->size; ++ii) {
    Vertex *vertex;
    Edge *edge;
    vertex = graph->vertex[ii];
    printf ("neighbors of %s:\n", vertex->name);
    for (edge = vertex->out; edge != NULL; edge = edge->next) {
      printf ("  %-10s (cost %d)\n", edge->dst->name, edge->cost);
    }
    printf ("\n");
  }
  
  g_delete (graph);
  
  return 0;
}
