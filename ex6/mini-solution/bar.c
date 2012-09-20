#include "bar.h"
#include <stdio.h>

void bar_hello (const Bar * bar)
{
  int ii;
  for (ii = 0; ii < bar->num; ++ii)
    putchar (bar->letter);
  printf (" hello from bar!\n");
}
