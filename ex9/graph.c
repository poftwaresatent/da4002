#include "graph.h"
#include <err.h>
#include <string.h>


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


Edge * v_connect (Vertex *src, Vertex *dst, double cost)
{
  Edge *ee = e_new (dst, cost);
  ee->next = src->out;
  src->out = ee;
  return ee;
}


Edge * e_new (Vertex *dst, double cost)
{
  Edge *ee = malloc (sizeof *ee);
  if (NULL == ee)
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  ee->next = NULL;
  ee->dst = dst;
  ee->cost = cost;
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
  int ii;
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


Vertex * g_vertex (Graph *gg, const char *name)
{
  Vertex *vv;
  int ii;
  for (ii = 0; ii < gg->size; ++ii)
    if (0  == strcmp (name, gg->vertex[ii]->name))
      return gg->vertex[ii];
  gg->vertex = realloc (gg->vertex, (gg->size + 1) * sizeof *(gg->vertex));
  if (NULL == gg)
    err (EXIT_FAILURE, __FILE__": %s: realloc", __func__);
  vv = v_new (name);
  gg->vertex[gg->size++] = vv;
  return vv;
}


Edge * g_connect (Graph *gg, const char *src, const char *dst, double cost)
{
  return v_connect (g_vertex (gg, src), g_vertex (gg, dst), cost);
}
