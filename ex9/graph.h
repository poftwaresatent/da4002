#ifndef ITADS_EX9_GRAPH_H
#define ITADS_EX9_GRAPH_H

#include <stdlib.h>


typedef struct vertex_s {
  /*
    adjacency list attributes
  */
  struct edge_s *out;
  
  /*
    payload data
  */
  const char * name;
  double value;
} Vertex;


typedef struct edge_s {
  /*
    adjacency list attributes
  */
  struct edge_s *next;
  struct vertex_s *dst;
  
  /*
    payload data
  */
  double cost;
} Edge;


typedef struct graph_s {
  Vertex **vertex;
  size_t size;
} Graph;


Vertex * v_new (const char *name);

void v_delete (Vertex *vv);

Edge * v_connect (Vertex *src, Vertex *dst, double cost);

Edge * e_new (Vertex *dst, double cost);

void e_delete (Edge *ee);

Graph * g_new ();

void g_delete (Graph *gg);

Vertex * g_vertex (Graph *gg, const char *name);

Edge * g_connect (Graph *gg, const char *src, const char *dst, double cost);


#endif /* ITADS_EX9_GRAPH_H */
