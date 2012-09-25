#include "clockms.h"
#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <unistd.h>


int main (int argc, char ** argv)
{
  for (;;) {
    printf ("%f\n", clockms ());
    usleep (100000);
  }
  return 0;
}
