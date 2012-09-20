#include "foo.h"
#include "bar.h"
#include <stdio.h>


int main (int argc, char ** argv)
{
  Bar bar;
  bar.num = 3;
  bar.letter = 'b';
  
  printf ("hello from main-mini!\n");
  foo_hello (2, 'f');
  bar_hello (&bar);
  
  return 0;
}
