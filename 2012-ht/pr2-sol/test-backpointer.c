#include <stdio.h>
#include <stdlib.h>
#include <err.h>


typedef struct {
  int above, left, best;
} State;


int main (int argc, char ** argv)
{
  State **matrix;
  int nrows, ncols;
  int ir, ic;
  
  /*
    Initialize and allocate a 5x7 matrix of State elements. Otherwise
    it's the same as test-propagation-example.c
  */
  nrows = 5;
  ncols = 7;
  matrix = malloc (nrows * sizeof(*matrix));
  if (NULL == matrix)
    err (EXIT_FAILURE, "malloc rows");
  for (ir = 0; ir < nrows; ++ir) {
    /*
      Notice that we use calloc instead of malloc here. The calloc
      function initializes the allocated data with zeros.
     */
    matrix[ir] = calloc (ncols, sizeof(**matrix));
    if (NULL == matrix[ir])
      err (EXIT_FAILURE, "calloc row %d", ir);
  }
  for (ic = 0; ic < ncols; ++ic)
    if (ic % 2)
      matrix[0][ic].best = -ic;
    else
      matrix[0][ic].best = 2*ic;
  for (ir = 0; ir < nrows; ++ir)
    if (ir % 2)
      matrix[ir][0].best = ir;
    else
      matrix[ir][0].best = -2*ir;
  
  /*
    Propagate values, just as in test-propagation-example.c, but this
    time, we store each of the candidate values so that we can later
    reconstruct the backpointers.
   */
  for (ir = 1; ir < nrows; ++ir)
    for (ic = 1; ic < ncols; ++ic) {
      matrix[ir][ic].above = matrix[ir-1][ic-1].best + matrix[ir-1][ic].best;
      matrix[ir][ic].left = matrix[ir-1][ic-1].best + matrix[ir][ic-1].best;
      if (matrix[ir][ic].above < matrix[ir][ic].left)
	matrix[ir][ic].best = matrix[ir][ic].above;
      else
	matrix[ir][ic].best = matrix[ir][ic].left;
    }
  
  /*
    Print the matrix as a nice table. This time, we also print
    backpointer information for each element underneath the "best"
    member of each state.
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
      printf (" %3d", matrix[ir][ic].best);
    printf ("\n");
    printf ("  |");
    for (ic = 0; ic < ncols; ++ic) {
      /* the trick to printing backpointers, which can be a string of
	 0, 1, or 2 characters, is to allocate a buffer large enough
	 to hold the biggest string, but don't fill it entirely. The
	 buffer needs space for the '\0' character that terminates a C
	 string, so it must be 3 characters long in this case.
       */
      char buf[3], *cc;
      cc = buf;
      if (matrix[ir][ic].best == matrix[ir][ic].above)
	*(cc++) = 'A';		/* 'A' means a backpointer from above */
      if (matrix[ir][ic].best == matrix[ir][ic].left)
	*(cc++) = 'L';		/* 'L' means a backpointer from the left */
      *(cc++) = '\0';		/* always terminate the string */
      printf (" %3s", buf);     /* place the string into a field of width 3 */
    }
    printf ("\n  |\n");
  }
  
  /*
    Free the memory used by the matrix.
  */
  for (ir = 0; ir < nrows; ++ir)
    free (matrix[ir]);
  free (matrix);
  
  return 0;
}
