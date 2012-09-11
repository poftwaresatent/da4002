#include <stdio.h>

#define MAXNUM 20

int main (int argc, char ** argv)
{
  unsigned short count[MAXNUM - 1];
  int ii, num;
  
  for (ii = 0; ii < MAXNUM - 1; ++ii) {
    count[ii] = 0;
  }
  
  for (num = 2; num <= MAXNUM / 2; ++num) {
    for (ii = num * 2 - 2; ii <= MAXNUM - 2; ii += num) {
      ++(count[ii]);
    }
  }
  
  printf ("NUMBER OF INTEGER DIVISORS other than 1 or itself:\n");
  for (num = 2; num <= MAXNUM; ++num) {
    printf ("%3d ", num);
    for (ii = 0; ii < count[num-2]; ++ii) {
      putchar ('*');
    }
    putchar ('\n');
  }
  
  return 0;
}
