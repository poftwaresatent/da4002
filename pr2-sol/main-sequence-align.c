#include <stdio.h>
#include <ctype.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>


#define GAP_COST -5


typedef struct state_s {
  int v_ins;
  int v_del;
  int c_match;
  int v_match;
  int v_best;
} State;


typedef struct table_s {
  int srclen;
  int dstlen;
  char *src;
  char *dst;
  State **state;
} Table;


Table * table_new (char *src, char *dst)
{
  Table *tab;
  char *chk;
  int ii;
  
  /* Check that the strings contain letters only. */
  
  for (chk = src; *chk != '\0'; ++chk)
    if (0 == isalpha (*chk))
      errx (EXIT_FAILURE, "%s: invalid character %d in source", (int) *chk, __func__);
  for (chk = dst; *chk != '\0'; ++chk)
    if (0 == isalpha (*chk))
      errx (EXIT_FAILURE, "%s: invalid character %d in destination", (int) *chk, __func__);
  
  /* Allocate the table */
  
  if (NULL == (tab = malloc (sizeof *tab)))
    err (EXIT_FAILURE, "%s: malloc table", __func__);
  
  /* Initialize the memory structures stored in the table */
  
  tab->srclen = (int) strlen (src);
  tab->dstlen = (int) strlen (dst);
  
  if (NULL == (tab->src = strdup (src)))
    err (EXIT_FAILURE, "%s: strdup source", __func__);
  if (NULL == (tab->dst = strdup (dst)))
    err (EXIT_FAILURE, "%s: strdup destination", __func__);
  
  if (NULL == (tab->state = malloc ((tab->srclen + 1) * sizeof *(tab->state))))
    err (EXIT_FAILURE, "%s: malloc state table lines", __func__);
  for (ii = 0; ii <= tab->srclen; ++ii)
    if (NULL == (tab->state[ii] = calloc (tab->dstlen + 1, sizeof **(tab->state))))
      err (EXIT_FAILURE, "%s: calloc state table line %d", __func__, ii);
  
  /* Initialize the first row and the first column using the GAP_COST */
  
  for (ii = 0; ii <= tab->dstlen; ++ii)
    tab->state[0][ii].v_best = ii * GAP_COST;
  for (ii = 1; ii <= tab->srclen; ++ii)
    tab->state[ii][0].v_best = ii * GAP_COST;
  
  return tab;
}


void table_delete (Table *tab)
{
  int ii;
  for (ii = 0; ii <= tab->srclen; ++ii)
    free (tab->state[ii]);
  free (tab->state);
  free (tab->dst);
  free (tab->src);
  free (tab);
}


int match_cost (char aa, char bb)
{
  static char vowel[] = { 'a', 'e', 'i', 'o', 'u' };
  static int nvowels = sizeof vowel / sizeof *vowel;
  int ii;
  
  aa = tolower (aa);
  bb = tolower (bb);
  
  if (aa == bb)
    return 10;			/* perfect match */
  
  for (ii = 0; ii < nvowels; ++ii)
    if (aa == vowel[ii]) {
      for (ii = 0; ii < nvowels; ++ii)
	if (bb == vowel[ii])
	  return -2;		/* vowel to vowel */
      return -10;		/* vowel to consonant */
    }
  
  for (ii = 0; ii < nvowels; ++ii)
    if (bb == vowel[ii])
      return -10;		/* consonant to vowel */
  
  return -4;			/* consonant to consonant */
}


int main (int argc, char **argv)
{
  Table *tab;
  int ii, jj, best;
  
  if (argc < 3)
    errx (EXIT_FAILURE, "please provide two strings on the command line");
  tab = table_new (argv[1], argv[2]);
  
  for (ii = 1; ii <= tab->srclen; ++ii) {
    for (jj = 1; jj <= tab->dstlen; ++jj) {
      
      tab->state[ii][jj].v_ins = tab->state[ii][jj-1].v_best + GAP_COST;
      best = tab->state[ii][jj].v_ins;
      
      tab->state[ii][jj].v_del = tab->state[ii-1][jj].v_best + GAP_COST;
      if (best < tab->state[ii][jj].v_del)
	best = tab->state[ii][jj].v_del;
      
      tab->state[ii][jj].v_match
	= tab->state[ii-1][jj-1].v_best
	+ match_cost (tab->src[ii-1], /* use ii-1 because of the extra "gap" at the beginning */
		      tab->dst[jj-1]);
      if (best < tab->state[ii][jj].v_match)
	best = tab->state[ii][jj].v_match;
      
      printf ("  %3d", best);
      tab->state[ii][jj].v_best = best;
    }
    printf ("\n");
  }
  
  table_delete (tab);
  
  return 0;
}
