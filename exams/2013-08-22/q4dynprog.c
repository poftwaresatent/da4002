#include <stdlib.h>
#include <stdio.h>

int calc (int i) {
  int gg, g1, g2, g3;
  if (i <= 2) {
    return 0;
  }
  if (i == 3) {
    return 1;
  }
  g1 = 1;
  g2 = 0;
  g3 = 0;
  while (i >= 4) {
    gg = 2 * g3 - g2 + g1;
    g3 = g2;
    g2 = g1;
    g1 = gg;
    --i;
  }
  return gg;
}

void print (int n) {
  int i;
  printf ("print(%d):", n);
  for (i = 1; i <= n; i++) {
    printf (" %d", calc (i));
  }
  printf ("\n");
}

int main (int argc, char ** argv)
{
  int n;
  for (n = 1; n <= 20; n++) {
    print (n);
  }
  return 0;
}
