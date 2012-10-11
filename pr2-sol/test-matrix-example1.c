#include <stdio.h>
#include <stdlib.h>
#include <err.h>


int main (int argc, char ** argv)
{
  int *matrix; /* the matrix is "just" a pointer to the first element */
  int nrows, ncols;
  int ir, ic;
  
  /*
    Initialize and allocate a 5x7 matrix.
  */
  nrows = 5;
  ncols = 7;
  matrix = malloc (nrows * ncols * sizeof(int));
  if (NULL == matrix)
    err (EXIT_FAILURE, "malloc");
  
  /*
    Fill the matrix with some example values. Notice that the array
    index is one-dimensional: in order to access the element at
    (ir,ic) you have to translate it into the index ir+ic*ncols.
  */
  for (ir = 0; ir < nrows; ++ir)
    for (ic = 0; ic < ncols; ++ic)
      if ((ir + ic) % 2)
	matrix[ir + ic*ncols] = -10*ic - ir;
      else
	matrix[ir + ic*ncols] = 10*ir + ic;
  
  /*
    Print the matrix as a nice table with a header row that lists the
    column indices, a header column which shows the row indices, and
    the values right-aligned into a field of width 3.
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
      printf (" %3d", matrix[ir + ic*ncols]);
    printf ("\n");
  }
  
  /*
    Free the memory used by the matrix.
  */
  free (matrix);
  
  return 0;
}
