#include <stdio.h>

main ()
{
  int c;
  unsigned long nc = 0, nl = 0;
  while (EOF != (c = getchar())) {
    putchar (c);
    ++nc;
    if ('\n' == c)
      ++nl;
  }
  printf ("\nL:%lu C:%lu\n", nl, nc);
}
