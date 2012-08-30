#include <stdio.h>

static int dcnt;

void pbin (unsigned long value)
{
  if (--dcnt <= 0) {
    return;
  }
  if (value >= 2) {
    pbin (value / 2);
  }
  printf ("%lu", value % 2);
}

int main (int argc, char **argv)
{
  int foo = 42117039;
  char bar = -17;
  unsigned char baz = 201;
  double pi = 3.14159265359;
  unsigned long *hack;
  
  printf ("int %d\n  hex %x\n  bin ", foo, foo);
  dcnt = 8 * sizeof(foo);
  hack = &foo;
  pbin (*hack);
  printf ("\n");
  
  printf ("char %d\n  hex %x\n  bin ", bar, bar);
  dcnt = 8 * sizeof(bar);
  hack = &bar;
  pbin (*hack);
  printf ("\n");
  
  printf ("unsigned char %u\n  hex %x\n  bin ", baz, baz);
  dcnt = 8 * sizeof(baz);
  hack = &baz;
  pbin (*hack);
  printf ("\n");
  
  printf ("double %g\n  hex %lx\n  bin ", pi, *hack);
  dcnt = 8 * sizeof(pi);
  pbin (*hack);
  printf ("\n");
  
  return 0;
}
