#include <stdio.h>
#include <ctype.h>

#define IN  1  /* inside a word */
#define OUT 0  /* outside a word */

int main (int argc, char ** argv)
{
  int c, state = OUT;
  unsigned long n = 0;
  while (EOF != (c = getchar())) {
    putchar (c);
    if (ispunct(c) || isspace(c))
      state = OUT;
    else if (state == OUT) {
      state = IN;
      ++n;
    }
  }
  printf ("\n%lu words\n", n);
  return 0;
}
