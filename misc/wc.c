#include <stdio.h>
#include <ctype.h>
#define IN  1  /* inside a word */
#define OUT 0  /* outside a word */
int main (int argc, char **argv) {
  int c, nl, nw, nc, state;
  state = OUT;
  nl = nw = nc = 0;
  while (EOF != (c = getchar())) {
    ++nc;
    if ('\n' == c)
      ++nl;
    if (ispunct(c) || isspace(c))
      state = OUT;
    else if (state == OUT) {
      state = IN;
      ++nw;
    }
  }
  printf ("%d %d %d\n", nl, nw, nc);
  return 0;
}