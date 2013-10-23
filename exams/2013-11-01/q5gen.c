#include <err.h>
#include <string.h>
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


//////////////////////////////////////////////////


Vertex * v_new (const char *name)
{
  Vertex *vv = malloc (sizeof *vv);
  if (NULL == vv)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  vv->out = NULL;
  vv->name = strdup (name);
  if (NULL == vv->name)
    err (EXIT_FAILURE, __FILE__": %s: strdup", __func__);
  vv->value = 0;
  return vv;
}


void v_delete (Vertex *vv)
{
  free ((void*)vv->name);
  free (vv);
}


Edge * e_new (Vertex *dst, int cost)
{
  Edge *ee = malloc (sizeof *ee);
  if (NULL == ee)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  ee->next = NULL;
  ee->dst = dst;
  ee->cost = cost;
  return ee;
}


Edge * v_connect (Vertex *src, Vertex *dst, int cost)
{
  Edge *ee = e_new (dst, cost);
  ee->next = src->out;
  src->out = ee;
  return ee;
}


void e_delete (Edge *ee)
{
  free (ee);
}


Graph * g_new ()
{
  Graph *gg = malloc (sizeof *gg);
  if (NULL == gg)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  gg->vertex = NULL;
  gg->size = 0;
  return gg;
}


void g_delete (Graph *gg)
{
  size_t ii;
  for (ii = 0; ii < gg->size; ++ii) {
    Edge *ee;
    for (ee = gg->vertex[ii]->out; ee != NULL; /**/) {
      Edge *tmp = ee->next;
      e_delete (ee);
      ee = tmp;
    }
    v_delete (gg->vertex[ii]);
  }
  free (gg->vertex);
  free (gg);
}


Vertex * g_find (Graph *gg, const char *name)
{
  size_t ii;
  for (ii = 0; ii < gg->size; ++ii)
    if (0  == strcmp (name, gg->vertex[ii]->name))
      return gg->vertex[ii];
  return NULL;
}


Vertex * g_vertex (Graph *gg, const char *name)
{
  Vertex *vv = g_find (gg, name);
  if (NULL != vv)
    return vv;
  gg->vertex = realloc (gg->vertex, (gg->size + 1) * sizeof *(gg->vertex));
  if (NULL == gg)
    err (EXIT_FAILURE, __FILE__": %s: realloc", __func__);
  vv = v_new (name);
  gg->vertex[gg->size++] = vv;
  return vv;
}


Edge * g_connect (Graph *gg, const char *src, const char *dst, int cost)
{
  return v_connect (g_vertex (gg, src), g_vertex (gg, dst), cost);
}


void g_print_dot (Graph *gg, FILE *stream)
{
  size_t ii;
  fprintf (stream, "digraph \"ex9\" {\n  graph [overlap=scale];\n");
  for (ii = 0; ii < gg->size; ++ii) {
    Vertex *src;
    src = gg->vertex[ii];
    fprintf (stream, "  \"%s\" [label=\"%s\\n%d\"%s];\n",
	     src->name, src->name, src->value,
	     src->value < 0 ? ",style=dotted" : (src->value == 0 ? ",style=bold" : ""));
  }
  for (ii = 0; ii < gg->size; ++ii) {
    Vertex *src;
    Edge *ee;
    src = gg->vertex[ii];
    for (ee = src->out; ee != NULL; ee = ee->next)
      fprintf (stream, "  \"%s\" -> \"%s\" [label=\"%d\",len=2%s];\n",
	       src->name, ee->dst->name, ee->cost,
	       src->value < 0 ? ",style=dotted" : (ee->dst->value == src->value + ee->cost) ? ",style=bold" : "");
  }
  fprintf (stream, "}\n");
}


void g_print (Graph *gg, FILE *stream)
{
  size_t ii;
  /* fprintf (stream, "vertices:\n"); */
  for (ii = 0; ii < gg->size; ++ii) {
    Vertex *src;
    src = gg->vertex[ii];
    fprintf (stream, "  %-10s\t%d\n", src->name, src->value);
  }
  /* fprintf (stream, "edges:\n"); */
  /* for (ii = 0; ii < gg->size; ++ii) { */
  /*   Vertex *src; */
  /*   Edge *ee; */
  /*   src = gg->vertex[ii]; */
  /*   for (ee = src->out; ee != NULL; ee = ee->next) */
  /*     fprintf (stream, "  %s -> %s\tc: %d\n", src->name, ee->dst->name, ee->cost); */
  /* } */
}


void g_parse (Graph *gg, FILE *stream)
{
  int status, cost;
  char src[100], dst[100];
  src[99] = '\0';
  dst[99] = '\0';
  
  for (;;) {
    status = fscanf (stream, " %99s %99s %d", src, dst, &cost);
    if (EOF == status)
      break;
    if (3 != status)
      errx (EXIT_FAILURE, __FILE__": %s: expected two strings and an integer", __func__);
    g_connect (gg, src, dst, cost);
  }
}


void g_load (Graph *gg, const char *fname)
{
  FILE *stream;
  if (NULL == (stream = fopen (fname, "r")))
    err (EXIT_FAILURE, __FILE__": %s: fopen %s", __func__, fname);
  g_parse (gg, stream);
  fclose (stream);
}


int main (int argc, char ** argv)
{
  Graph * gg;
  if (argc < 2) {
    errx (EXIT_FAILURE, "expected adj file name");
  }
  gg = g_new ();
  g_load (gg, argv[1]);
  g_print_dot (gg, stdout);
  g_delete (gg);
  return 0;
}
