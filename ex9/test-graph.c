#include "graph.h"

int main (int argc, char **argv)
{
  Graph *gg;
  gg = g_new ();
  g_connect (gg, "foo", "bar", 42);
  g_delete (gg);
  return 0;
}
