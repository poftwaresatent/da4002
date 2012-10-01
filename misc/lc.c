#include <stdio.h>

int main (int argc, char ** argv)
{
  int c;
  unsigned long n = 0;
  while (EOF != (c = getchar())) {
    putchar (c);
    if ('\n' == c)
      ++n;
  }
  printf ("\n%lu lines\n", n);
  return 0;
}
