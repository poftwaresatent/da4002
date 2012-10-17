#ifndef ITADS_EX9_GRAPH_H
#define ITADS_EX9_GRAPH_H

#include <stdlib.h>
#include <stdio.h>


typedef struct vertex_s {
  /*
    head of the adjacency list
  */
  struct edge_s *out;
  
  /*
    payload data
  */
  const char * name;
  int value;
} Vertex;


typedef struct edge_s {
  /*
    adjacency list attributes: pointer to the next edge, and to the
    vertex at the other end of this (current) edge
  */
  struct edge_s *next;
  struct vertex_s *dst;
  
  /*
    payload data
  */
  int cost;
} Edge;


typedef struct graph_s {
  /*
    For simplicity, we store all the vertices in an array. This makes
    searching for a vertex very inefficient, but it is easy to
    implement and good enough for this example.
  */
  Vertex **vertex;
  size_t size;
} Graph;


Vertex * v_new (const char *name);

void v_delete (Vertex *vv);

Edge * v_connect (Vertex *src, Vertex *dst, int cost);

Edge * e_new (Vertex *dst, int cost);

void e_delete (Edge *ee);

Graph * g_new ();

void g_delete (Graph *gg);

Vertex * g_find (Graph *gg, const char *name);

Vertex * g_vertex (Graph *gg, const char *name);

Edge * g_connect (Graph *gg, const char *src, const char *dst, int cost);

void g_print (Graph *gg, FILE *stream);

void g_print_dot (Graph *gg, FILE *stream);

void g_parse (Graph *gg, FILE *stream);

void g_load (Graph *gg, const char *fname);


#endif /* ITADS_EX9_GRAPH_H */
