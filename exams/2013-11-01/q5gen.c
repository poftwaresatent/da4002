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


//////////////////////////////////////////////////


typedef struct item_s {
  int key;
  Vertex *vv;
} Item;

static Item *heap;
static size_t heaplen;


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


void dumpqueue (const char *foo)
{
  size_t ii;
  printf ("  %s\n", foo);
  if (0 == heaplen) {
    printf ("    EMPTY\n");
    return;
  }
  for (ii = 1; ii <= heaplen; ++ii)
    printf ("    %d %p %s\n", heap[ii].key, heap[ii].vv, heap[ii].vv->name);
}


void dijkstra (Vertex *vv)
{
  vv->value = 0;
  enqueue (0, vv);
  for (;;) {
    Edge *ee;
    Item it = dequeue ();
    if (NULL == it.vv)
      break;
    for (ee = it.vv->out; ee != NULL; ee = ee->next) {
      int key = it.vv->value + ee->cost;
      if ((ee->dst->value < 0) || (ee->dst->value > key)) {
	ee->dst->value = key;
	enqueue (key, ee->dst);
      }
    }
  }
}


//////////////////////////////////////////////////


int main (int argc, char **argv)
{
  Graph *graph;
  Vertex *start;
  size_t ii;
  
  if (argc < 3)
    errx (EXIT_FAILURE, "Please specify a file name and a start node name.");
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
