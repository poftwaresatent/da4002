#include <stdio.h>
#include <ctype.h>
#include <string.h>

main ()
{
  int c;
  unsigned long n[10];
  memset (n, 0, sizeof(n));
  while (EOF != (c = getchar())) {
    putchar (c);
    if ('0' <= c && '9' >= c)
      ++n[c - '0'];
  }
  printf ("\ndigits:\n");  
  for (c = 0; c < 10; ++c)
    printf ("  %d:\t%lu\n", c, n[c]);
}
