#include <stdlib.h>
#include <stdio.h>

static int * memo;

int calc (int i) {
  if (i <= 2) {
    return 0;
  }
  if (i == 3) {
    return 1;
  }
  if (memo[i-4] < 0) {		/* the first memo is for i=4 */
    memo[i-4] = 2 * calc (i-3) - calc (i-2) + calc (i-1);
  }
  return memo[i-4];
}

void print (int n) {
  int i;
  memo = malloc ((n-3) * sizeof *memo);
  for (i = 0; i < n-3; i++) {
    memo[i] = -1;
  }
  printf ("print(%d):", n);
  for (i = 1; i <= n; i++) {
    printf (" %d", calc (i));
  }
  printf ("\n");
  free (memo);
}

int main (int argc, char ** argv)
{
  int n;
  for (n = 1; n <= 20; n++) {
    print (n);
  }
  return 0;
}
