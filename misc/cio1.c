#include <stdio.h>

main ()
{
  int c;
  unsigned long n;
  n = 0;
  c = getchar();     /* from stdio.h */
  while (EOF != c) { /* End Of File */
    putchar (c);
    ++n;
    c = getchar();
  }
  printf ("\ntotal: %lu\n", n);
}
