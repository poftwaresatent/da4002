#include <stdlib.h>
#include <stdio.h>

static int *count;

int calc (int i) {
  if (i > 0) {
    ++count[i-1];
  }
  if (i <= 2) {
    return 0;
  }
  if (i == 3) {
    return 1;
  }
  return 2 * calc (i-3) - calc (i-2) + calc (i-1);
}

void print (int n) {
  int i;
  count = calloc (n, sizeof *count);
  printf ("--------------------------------------------------\nprint(%d):", n);
  for (i = 1; i <= n; i++) {
    printf (" %d", calc (i));
  }
  printf ("\ncounts:\n");
  for (i = 1; i <= n; i++) {
    printf ("[%3d] %5d\n", i, count[i-1]);
  }
  free (count);
}

int main (int argc, char ** argv)
{
  int n;
  for (n = 1; n <= 10; n++) {
    print (n);
  }
  return 0;
}
