#include <stdio.h>
#include <string.h>

int main (int argc, char ** argv)
{
  size_t numchars;
  int ii, jj, kk;
  char tmp;
  
  for (ii = 1; ii < argc; ++ii) {
    printf ("\nin:  %s\n", argv[ii]);
    
    numchars = strlen (argv[ii]);
    for (jj = 0; jj < numchars; ++jj) {
      for (kk = 1; kk < numchars; ++kk) {
	if (argv[ii][kk] < argv[ii][kk - 1]) {
	  tmp = argv[ii][kk];
	  argv[ii][kk] = argv[ii][kk - 1];
	  argv[ii][kk - 1] = tmp;
	}
      }
    }
    
    printf ("out: %s\n", argv[ii]);
  }
  
  return 0;
}
