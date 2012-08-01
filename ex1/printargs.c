#include <stdio.h>
#include <string.h>

int main (int argc, char ** argv)
{
  int ii;
  for (ii = 0; ii < argc; ++ii) {
    size_t len = strlen (argv[ii]);
    printf ("argv[%d] (length %zu):\t`%s'\n", ii, len, argv[ii]);
  }
  return 0;
}
