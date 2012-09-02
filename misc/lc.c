#include <stdio.h>

main ()
{
  int c;
  unsigned long n = 0;
  while (EOF != (c = getchar())) {
    putchar (c);
    if ('\n' == c)
      ++n;
  }
  printf ("\n%lu lines\n", n);
}
