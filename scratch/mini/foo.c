#include <stdio.h>

void foo_hello (int num, char letter)
{
  for (/**/; num > 0; --num)
    putchar (letter);
  printf (" hello from foo!\n");
}
