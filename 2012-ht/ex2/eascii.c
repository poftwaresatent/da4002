#include <stdio.h>
#include <ctype.h>

int main (int argc, char ** argv)
{
  int ii;
  for (ii = 1; ii < argc; ++ii) {
    char * cc = argv[ii];
    printf ("%s\n  car:", cc);
    for (; *cc != '\0'; ++cc) {
      if (isprint(*cc)) {
	printf (" '%c'", *cc);
      }
      else {
	printf ("  . ");
      }
    }
    printf ("\n  dec:");
    for (cc = argv[ii]; *cc != '\0'; ++cc) {
      printf (" %3d", *cc);
    }
    printf ("\n  hex:");
    for (cc = argv[ii]; *cc != '\0'; ++cc) {
      printf ("  %02x", *cc);
    }
    printf ("\n");
  }
  return 0;
}
