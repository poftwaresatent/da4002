#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge (int * arr, int * tmp, int beg, int mid, int end)
{
  int ii = beg;
  int jj = mid;
  int kk = beg;
  
  while (ii < mid && jj < end) {
    if (arr[ii] < arr[jj]) {
      tmp[kk++] = arr[ii++];
    }
    else {
      tmp[kk++] = arr[jj++];
    }
  }
  while (ii < mid) {
    tmp[kk++] = arr[ii++];
  }
  while (jj < end) {
    tmp[kk++] = arr[jj++];
  }
  
  for (ii = beg; ii < end; ++ii) {
    arr[ii] = tmp[ii];
  }
}


void dump (int * arr, int beg, int end)
{
  int ii;
  
  printf ("[%2d:", beg);
  for (ii = beg; ii < end; ++ii) {
    printf ("  %2d", arr[ii]);
  }
  printf ("]");
}


void msort_rec (int * arr, int * tmp, int beg, int end)
{
  int len, mid;
  
  len = end - beg;
  if (1 >= len) {
    dump (arr, beg, end);
    printf ("\n");
    return;
  }
  
  mid = beg + len / 2;
  msort_rec (arr, tmp, beg, mid);
  msort_rec (arr, tmp, mid, end);
  
  dump (arr, beg, mid);
  printf (" + ");
  dump (arr, mid, end);
  printf (" -> ");
  
  merge (arr, tmp, beg, mid, end);
  
  dump (arr, beg, end);
  printf ("\n");
}


void merge_sort (int * arr, int len)
{
  int * tmp = malloc (len * sizeof *tmp);
  msort_rec (arr, tmp, 0, len);
  free (tmp);
}


int main (int argc, char ** argv)
{
  static int const input[] = { 15, 3, 92 };
  int * output;
  
  output = malloc (sizeof input);
  memcpy (output, input, sizeof input);
  
  merge_sort (output, (sizeof input) / (sizeof *input));
  
  free (output);
  
  return 0;
}
