#include <stdio.h>

int main (int argc, char ** argv)
{
  int aa, bb;
  for (aa = 1; aa < 1000; ++aa)
    for (bb = aa+1; bb < 1000; ++bb)
      if (0 == ((aa*aa + bb*bb + 1) % (aa*bb)))
	printf ("%d %d\n", aa, bb);
  return 0;
}
