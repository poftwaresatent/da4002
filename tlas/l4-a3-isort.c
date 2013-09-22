#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void insertion_sort (int * arr, int len)
{
  int ii, jj, tmp;
  
  for (ii = 1; ii < len; ++ii) {
    
    tmp = arr[ii];
    for (jj = ii; jj > 0; --jj) {
      if (tmp >= arr[jj-1]) {
	break;
      }
      arr[jj] = arr[jj-1];
    }
    arr[jj] = tmp;
    
  }
}


int main (int argc, char ** argv)
{
  static int const input[] = { 15, 3, 92, 14, 4 };
  int * output;
  int ii;
  
  output = malloc (sizeof input);
  memcpy (output, input, sizeof input);
  
  insertion_sort (output, (sizeof input) / (sizeof *input));
  
  for (ii = 0; ii < (sizeof input) / (sizeof *input); ++ii) {
    printf ("  %2d", output[ii]);
  }
  printf ("\n");
  
  free (output);
  
  return 0;
}
