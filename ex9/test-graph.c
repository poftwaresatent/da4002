#include "graph.h"

int main (int argc, char **argv)
{
  Graph *gg;
  
  gg = g_new ();
  if (argc > 1)
    g_load (gg, argv[1]);
  else
    g_parse (gg, stdin);
  g_print_dot (gg, stdout);
  
  g_delete (gg);
  
  return 0;
}
