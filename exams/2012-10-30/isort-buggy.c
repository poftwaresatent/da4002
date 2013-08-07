#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>


void isort_correct (int *arr, int len)
{
  int ii;
  for (ii = 1; ii < len; ++ii) {
    int jj, ival;
    ival = arr[ii];
    for (jj = ii; jj > 0; --jj) {
      if (ival >= arr[jj-1])
	break;
      arr[jj] = arr[jj-1];
    }
    arr[jj] = ival;
  }
}


void isort_buggy (int *arr, int len)
{
  int ii;
  for (ii = 1; ii < len; ++ii) {
    int jj;
    for (jj = ii; jj > 0; --jj) {
      if (arr[ii] >= arr[jj-1])
	break;
      arr[jj] = arr[jj-1];
    }
    arr[jj] = arr[ii];
  }
}


void isort_mathew (int *arr, int len)
{
  int ii;
  for (ii = 0; ii < len; ++ii) {
    int jj;
    for (jj = ii; jj < len - 1; ++jj) {
      if (arr[ii] > arr[jj-1])
	break;
      arr[jj] = arr[ii-1];
    }
    arr[jj] = arr[ii];
  }
}


int main (int argc, char ** argv)
{
  int data[10] = { 6, 0, 7, 3, 8, 5, 1, 4, 9, 2 };
  int dup[10];
  int ii;
  
  memcpy (dup, data, 10 * sizeof *dup);
  isort_correct (dup, 10);
  for (ii = 0; ii < 10; ++ii)
    printf ("  %d", dup[ii]);
  printf ("\n");
  
  memcpy (dup, data, 10 * sizeof *dup);
  isort_mathew (dup, 10);
  for (ii = 0; ii < 10; ++ii)
    printf ("  %d", dup[ii]);
  printf ("\n");
  
  return 0;
}
