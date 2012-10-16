#include "graph.h"
#include <stdio.h>
#include <err.h>


int main (int argc, char **argv)
{
  Graph *gg;
  char src[100], dst[100];
  int cost;
  int status;
  src[99] = '\0';
  dst[99] = '\0';
  
  gg = g_new ();
  
  for (;;) {
    status = fscanf (stdin, " %99s %99s %d", src, dst, &cost);
    if (EOF == status)
      break;
    if (3 != status)
      errx (EXIT_FAILURE, "expected two strings and an integer");
    g_connect (gg, src, dst, cost);
  }
  g_print_dot (gg, stdout);
  
  g_delete (gg);
  
  return 0;
}
