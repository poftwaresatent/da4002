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


int move (int size, char src, char dst)
{
  if (1 >= size) {
    printf ("disk 1 from %c to %c\n", src, dst);
    return 1;
  }

  int cnt = 1;
  cnt += move(size-1, src, other(src, dst));
  printf ("disk %d from %c to %c\n", size, src, dst);
  cnt += move(size-1, other(src, dst), dst);
  return cnt;
}


int main (int argc, char ** argv)
{
  int size;
  for (size = 1; size < 6; ++size) {
    printf ("\nsize %d:\n", size);
    printf ("hanoi size %d takes %d moves\n", size, move(size, 'A', 'B'));
  }
  return 0;
}
