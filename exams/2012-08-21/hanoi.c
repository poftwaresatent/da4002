// gcc -Wall -o hanoi hanoi.c

#include <stdio.h>


char other (char src, char dst)
{
  switch (src) {
  case 'A':
    return dst == 'B' ? 'C' : 'B';
  case 'B':
    return dst == 'A' ? 'C' : 'A';
  }
  return dst == 'A' ? 'B' : 'A';
}


int move (int verbose, int size, char src, char dst)
{
  if (1 >= size) {
    if (verbose) {
      printf ("disk 1 from %c to %c\n", src, dst);
    }
    return 1;
  }

  int cnt = 1;
  cnt += move(verbose, size-1, src, other(src, dst));
  if (verbose) {
    printf ("disk %d from %c to %c\n", size, src, dst);
  }
  cnt += move(verbose, size-1, other(src, dst), dst);
  return cnt;
}


int move2 (int verbose, int size, char aa, char bb, char cc)
{
  if (1 >= size) {
    if (verbose) {
      printf ("disk 1 from %c to %c\n", aa, cc);
    }
    return 1;
  }
  
  int cnt = 1;
  cnt += move2(verbose, size-1, aa, cc, bb);
  if (verbose) {
    printf ("disk %d from %c to %c\n", size, aa, cc);
  }
  cnt += move2(verbose, size-1, bb, aa, cc);
  return cnt;
}


int main (int argc, char ** argv)
{
  int size;
  for (size = 1; size < 6; ++size) {
    printf ("\nsize %d:\n", size);
    printf ("hanoi size %d takes %d moves\n", size, move2(1, size, 'A', 'B', 'C'));
  }
  return 0;
}
