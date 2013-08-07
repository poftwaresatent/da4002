#include <stdio.h>
#include "ex-preprocessor-commands.h"

#define FORTYTWO 42
#define SOMESTRING "some string"
#define TWOPI 6.28318530718

#ifndef BLAH
# define BLAH
#else
# define BLAHBLAH
#endif

int main(int argc, char ** argv)
{
  return 0;
}
