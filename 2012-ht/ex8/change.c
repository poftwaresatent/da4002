#include <stdio.h>
#include <stdlib.h>
#include <err.h>


int main (int argc, char ** argv)
{
  int ndenom;
  int kmax;
  int *denom;
  struct {
    int *value;
    int *count;
    int best;
  } *tab;
  int ii, jj;
  
  ndenom = 0;
  kmax = 0;
  denom = NULL;
  if (argc > 1) {
    if (1 != sscanf (argv[1], "%d", &kmax))
      errx (EXIT_FAILURE, "arg 1 `%s': positive int expected", argv[1]);
    if (kmax <= 0)
      errx (EXIT_FAILURE, "arg 1 (%d): positive int expected", kmax);
  }
  for (ii = 2; ii < argc; ++ii) {
    if (1 != sscanf (argv[ii], "%d", &jj))
      errx (EXIT_FAILURE, "arg %d `%s': positive int expected", ii, argv[ii]);
    if (jj <= 0)
      errx (EXIT_FAILURE, "arg %d (%d): positive int expected", ii, jj);
    ++ndenom;
    if (NULL == (denom = realloc (denom, ndenom * sizeof *denom)))
      err (EXIT_FAILURE, "realloc");
    denom[ndenom-1] = jj;
  }
  
  if (kmax == 0)
    kmax = 20;
  if (ndenom == 0) {
    ndenom = 3;
    denom = malloc (ndenom * sizeof *denom);
    denom[0] = 1;
    denom[1] = 3;
    denom[2] = 7;
  }
  
  tab = malloc ((kmax+1) * sizeof *tab);
  for (ii = 0; ii <= kmax; ++ii) {
    tab[ii].value = calloc (ndenom, sizeof(int));
    tab[ii].count = calloc (ndenom, sizeof(int));
  }
  
  tab[0].best = 0;
  
  for (ii = 1; ii <= kmax; ++ii) {
    
    for (jj = 0; jj < ndenom; ++jj) {
      tab[ii].count[jj] = 0;
      if (denom[jj] > ii)
	tab[ii].value[jj] = -1;
      else {
	tab[ii].value[jj] = 1 + tab[ii - denom[jj]].best;
	if (0 == jj)
	  tab[ii].best = tab[ii].value[jj];
	else if (tab[ii].best > tab[ii].value[jj])
	  tab[ii].best = tab[ii].value[jj];
      }
    }
    
    for (jj = ndenom - 1; jj >= 0; --jj)
      if (tab[ii].best == tab[ii].value[jj]) {
	int kprev = ii - denom[jj];
	tab[ii].count[jj] = 1;
	for (jj = 0; jj < ndenom; ++jj)
	  tab[ii].count[jj] += tab[kprev].count[jj];
	break;
      }
  }
  
  printf ("  K |");
  for (ii = 0; ii < ndenom; ++ii)
    printf (" C%-2d", denom[ii]);
  printf (" |  V |  choices and optimal sequence\n"
	  "----------------------------------------------------------------------\n");
  
  for (ii = 1; ii <= kmax; ++ii) {
    char sep;
    printf ("%3d |", ii);
    for (jj = 0; jj < ndenom; ++jj)
      if (0 < tab[ii].value[jj])
	printf (" %3d", tab[ii].value[jj]);
      else
	printf ("    ");
    printf (" | %2d |", tab[ii].best);
    for (jj = 0; jj < ndenom; ++jj)
      if (tab[ii].best == tab[ii].value[jj])
	printf (" %2d", denom[jj]);
      else
	printf ("   ");
    printf (" |");
    for (jj = 0, sep = ' '; jj < ndenom; ++jj) {
      int kk;
      for (kk = 0; kk < tab[ii].count[jj]; ++kk) {
	printf ("%c%d", sep, denom[jj]);
	sep = '+';
      }
    }
    printf ("\n");
  }
  
  for (ii = 0; ii <= kmax; ++ii) {
    free (tab[ii].value);
    free (tab[ii].count);
  }
  free (tab);
  free (denom);
  
  return 0;
}
