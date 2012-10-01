#include <stdio.h>

void move (int sz, char src, char dst)
{
  printf ("  disk %d: %c to %c\n", sz, src, dst);
}

void hanoi (int sz, char src, char dst, char tmp)
{
  if (1 >= sz)
    move (1, src, dst);
  else {
    hanoi (sz - 1, src, tmp, dst);
    move (sz, src, dst);
    hanoi (sz - 1, tmp, dst, src);
  }
}

int main (int argc, char ** argv)
{
  int sz;
  for (sz = 1; sz < 6; ++sz) {
    printf ("\nsize %d:\n", sz);
    hanoi (sz, 'A', 'C', 'B');
  }
  return 0;
}
