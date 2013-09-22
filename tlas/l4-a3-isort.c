#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void insertion_sort (int * arr, int len)
{
  int ii, jj, tmp;
  
  for (jj = 0; jj < len; ++jj) {
    printf ("  %2d", arr[jj]);
  }
  printf ("\n");
  
  for (ii = 1; ii < len; ++ii) {
    
    tmp = arr[ii];
    for (jj = ii; jj > 0; --jj) {
      if (tmp >= arr[jj-1]) {
	break;
      }
      arr[jj] = arr[jj-1];
    }
    arr[jj] = tmp;
    
    for (jj = 0; jj < len; ++jj) {
      printf ("  %2d", arr[jj]);
    }
    printf ("\n");
    
  }
}


int main (int argc, char ** argv)
{
  static int const input[] = { 15, 3, 92, 14, 4 };
  int * output;
  
  output = malloc (sizeof input);
  memcpy (output, input, sizeof input);
  
  insertion_sort (output, (sizeof input) / (sizeof *input));
  
  free (output);
  
  return 0;
}
