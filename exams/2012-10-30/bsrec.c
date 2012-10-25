#include <stdio.h>
#include <string.h>


int bsrec (char *str, char **arr, int low, int high)
{
  int mid, cmp;
  if (low > high) {
    return -1;
  }
  mid = (low + high) / 2;
  cmp = strcmp (str, arr[mid]);
  if (cmp > 0) {
    return bsrec (str, arr, mid + 1, high);
  }
  if (cmp < 0) {
    return bsrec (str, arr, low, mid - 1);
  }
  return mid;
}

int bsearch (char *str, char **arr, int len)
{
  return bsrec (str, arr, 0, len - 1);
}


int main (int argc, char **argv)
{
  int ii;
  
  if (3 > argc) {
    fprintf (stderr,
	     "Please provide a string and a list of strings (which should be sorted).\n"
	     "For example, give the following command:\n"
	     "  %s foo bar baz foo toto\n",
	     argv[0]);
    return 42;
  }
  
  ii = bsearch (argv[1], argv + 2, argc - 2);
  if (-1 == ii) {
    printf ("%s was not found\n", argv[1]);
  }
  else {
    printf ("%s was found at index %d\n", argv[1], ii);
  }
  
  return 0;
}
