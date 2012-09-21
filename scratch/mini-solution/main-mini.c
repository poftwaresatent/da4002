#include "toto.h"
#include <stdio.h>


int main (int argc, char ** argv)
{
  Bar tab[10];
  int ii;
  
  toto_init (tab, 10);
  for (ii = 0; ii < 10; ++ii)
    bar_hello (tab+ii);
  
  return 0;
}
