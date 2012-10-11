#include <stdio.h>
#include <stdlib.h>
#include <err.h>


int main (int argc, char ** argv)
{
  int **matrix;
  int nrows, ncols;
  int ir, ic;
  
  /*
    Initialize and allocate a 5x7 matrix. Here, we only initialize the
    first row and the first column, the other values will get filled
    in by the propoagation example (see below).
  */
  nrows = 5;
  ncols = 7;
  matrix = malloc (nrows * sizeof(int*));
  if (NULL == matrix)
    err (EXIT_FAILURE, "malloc rows");
  for (ir = 0; ir < nrows; ++ir) {
    matrix[ir] = malloc (ncols * sizeof(int));
    if (NULL == matrix[ir])
      err (EXIT_FAILURE, "malloc row %d", ir);
  }
  for (ic = 0; ic < ncols; ++ic)
    if (ic % 2)
      matrix[0][ic] = -ic;
    else
      matrix[0][ic] = 2*ic;
  for (ir = 0; ir < nrows; ++ir)
    if (ir % 2)
      matrix[ir][0] = ir;
    else
      matrix[ir][0] = -2*ir;
  
  /*
    Propagate values through the non-initialized part of the matrix by
    taking the minimum of two candidate values:
    - the sum of the cell above and above-left
    - the sum of the cell to the left and above-left
   */
  for (ir = 1; ir < nrows; ++ir)
    for (ic = 1; ic < ncols; ++ic) {
      int v1, v2;
      v1 = matrix[ir-1][ic-1] + matrix[ir-1][ic];
      v2 = matrix[ir-1][ic-1] + matrix[ir][ic-1];
      if (v1 < v2)
	matrix[ir][ic] = v1;
      else
	matrix[ir][ic] = v2;
    }
  
  /*
    Print the matrix as a nice table.
  */
  printf ("  |");
  for (ic = 0; ic < ncols; ++ic)
    printf (" %3d", ic);
  printf ("\n--+");
  for (ic = 0; ic < ncols; ++ic)
    printf ("----");
  printf ("\n");
  for (ir = 0; ir < nrows; ++ir) {
    printf ("%d |", ir);
    for (ic = 0; ic < ncols; ++ic)
      printf (" %3d", matrix[ir][ic]);
    printf ("\n");
  }
  
  /*
    Free the memory used by the matrix.
  */
  for (ir = 0; ir < nrows; ++ir)
    free (matrix[ir]);
  free (matrix);
  
  return 0;
}
