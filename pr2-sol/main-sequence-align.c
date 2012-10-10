#include <stdio.h>
#include <ctype.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>


#define GAP_COST -5


typedef struct {
  int v_ins;
  int v_del;
  int v_match;
  int v_best;
  char act[4];
} State;


typedef struct {
  int srclen;
  int dstlen;
  char *src;
  char *dst;
  State **state;
} Table;


typedef struct {
  char *srcbuf, *src;
  char *dstbuf, *dst;
  int isrc, idst, iact;
} Alignment;


Table * table_new (char *src, char *dst)
{
  Table *tab;
  char *chk;
  int ii;
  
  /* Check that the strings contain letters only. */
  
  for (chk = src; *chk != '\0'; ++chk)
    if (0 == isalpha (*chk))
      errx (EXIT_FAILURE, "%s: invalid character %d in source", __func__, (int) *chk);
  for (chk = dst; *chk != '\0'; ++chk)
    if (0 == isalpha (*chk))
      errx (EXIT_FAILURE, "%s: invalid character %d in destination", __func__, (int) *chk);
  
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
  
  /* tab->state[0][0].v_ins = -999; /\* use -999 so that there is no action associated with [0][0] *\/ */
  /* tab->state[0][0].v_del = -999; */
  /* tab->state[0][0].v_match = -999; */
  /* tab->state[0][0].v_best = 0; */
  for (ii = 1; ii <= tab->dstlen; ++ii) {
    tab->state[0][ii].v_best = ii * GAP_COST;
    tab->state[0][ii].v_ins = tab->state[0][ii].v_best;
    tab->state[0][ii].act[0] = 'i';
  }
  for (ii = 1; ii <= tab->srclen; ++ii) {
    tab->state[ii][0].v_best = ii * GAP_COST;
    tab->state[ii][0].v_del = tab->state[ii][0].v_best;
    tab->state[ii][0].act[0] = 'd';
  }
  
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
  int ii, jj;
  
  if (argc < 3)
    errx (EXIT_FAILURE, "please provide two strings on the command line");
  tab = table_new (argv[1], argv[2]);
  
  /***************************************************
   * propagate
   */
  
  for (ii = 1; ii <= tab->srclen; ++ii) {
    for (jj = 1; jj <= tab->dstlen; ++jj) {
      int best;
      char * act;
      
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
      
      act = tab->state[ii][jj].act;
      if (best == tab->state[ii][jj].v_match)
	*(act++) = 'm';
      if (best == tab->state[ii][jj].v_del)
	*(act++) = 'd';
      if (best == tab->state[ii][jj].v_ins)
	*(act++) = 'i';
      *(act++) = '\0';
      
      tab->state[ii][jj].v_best = best;
    }
  }
  
  /***************************************************
   * print
   */
  
  printf ("\n    _");
  for (ii = 1; ii <= tab->dstlen; ++ii)
    printf ("    %c", tab->dst[ii-1]);
  printf ("\n\n");
  for (ii = 0; ii <= tab->srclen; ++ii) {
    printf ("%c", ii == 0 ? '_' : tab->src[ii-1]);
    for (jj = 0; jj <= tab->dstlen; ++jj)
      printf (" % 4d", tab->state[ii][jj].v_best);
    printf ("\n ");
    for (jj = 0; jj <= tab->dstlen; ++jj)
      printf (" %4s", tab->state[ii][jj].act);
    printf ("\n\n");
  }
  
  /***************************************************
   * trace back
   */
  
  {
    Alignment *sol;
    int nsol = 1;
    int done;
    int buflen = tab->srclen + tab->dstlen + 1;
    
    if (NULL == (sol = malloc (sizeof *sol)))
      err (EXIT_FAILURE, "malloc sol");
    
    if (NULL == (sol[0].srcbuf = calloc (buflen, sizeof(char))))
      err (EXIT_FAILURE, "calloc sol[0].srcbuf");
    sol[0].src = sol[0].srcbuf + buflen - 1;
    if (NULL == (sol[0].dstbuf = calloc (buflen, sizeof(char))))
      err (EXIT_FAILURE, "calloc sol[0].dstbuf");
    sol[0].dst = sol[0].dstbuf + buflen - 1;
    sol[0].isrc = tab->srclen;
    sol[0].idst = tab->dstlen;
    sol[0].iact = 0;
    
    for (done = 0; done != 1; /**/) {
      int ncheck;
      done = 1;
      
      /* check for branches */
      
      ncheck = nsol;		/* we may end up adding to nsol, don't check those though */
      for (ii = 0; ii < ncheck; ++ii) {
	
	/* skip finished alignments */
	
	if (sol[ii].isrc == 0 && sol[ii].idst == 0)
	  continue;
	
	/* check whether we have a 2nd and a 3rd action */
	
	for (jj = 1; jj <= 2; ++jj) {
	  
	  /* no more actions when we hit the '\0' of the action string */
	  
	  if (tab->state[sol[ii].isrc][sol[ii].idst].act[jj] == '\0')
	    break;
	  
	  /* append a duplicate of sol[ii] that uses jj as iact */
	  
	  if (NULL == (sol = realloc (sol, (nsol + 1) * sizeof *sol)))
	    err (EXIT_FAILURE, "realloc sol");
	  
	  if (NULL == (sol[nsol].srcbuf = malloc ((buflen) * sizeof(char))))
	    err (EXIT_FAILURE, "malloc sol[nsol].srcbuf");
	  memcpy (sol[nsol].srcbuf, sol[ii].srcbuf, buflen * sizeof(char));
	  sol[nsol].src = sol[nsol].srcbuf + (sol[ii].src - sol[ii].srcbuf);
	  sol[nsol].isrc = sol[ii].isrc;
	  
	  if (NULL == (sol[nsol].dstbuf = malloc ((buflen) * sizeof(char))))
	    err (EXIT_FAILURE, "malloc sol[nsol].dstbuf");
	  memcpy (sol[nsol].dstbuf, sol[ii].dstbuf, buflen * sizeof(char));
	  sol[nsol].dst = sol[nsol].dstbuf + (sol[ii].dst - sol[ii].dstbuf);
	  sol[nsol].idst = sol[ii].idst;
	  
	  sol[nsol].iact = jj;
	  
	  ++nsol;
	}
      }
      
      /* update all alignment branches */
      
      for (ii = 0; ii < nsol; ++ii) {
	
	/* skip finished alignments */
	
	if (sol[ii].isrc == 0 && sol[ii].idst == 0)
	  continue;
	
	/* perform next action in the backtrace */
	
	done = 0;
	if (tab->state[sol[ii].isrc][sol[ii].idst].act[sol[ii].iact] == 'm') {
	  *(sol[ii].src--) = tab->src[--sol[ii].isrc];
	  *(sol[ii].dst--) = tab->dst[--sol[ii].idst];
	}
	else if (tab->state[sol[ii].isrc][sol[ii].idst].act[sol[ii].iact] == 'i') {
	  *(sol[ii].src--) = '_';
	  *(sol[ii].dst--) = tab->dst[--sol[ii].idst];
	}
	else if (tab->state[sol[ii].isrc][sol[ii].idst].act[sol[ii].iact] == 'd') {
	  *(sol[ii].src--) = tab->src[--sol[ii].isrc];
	  *(sol[ii].dst--) = '_';
	}
	else
	  errx (EXIT_FAILURE, "BUG: action %d  solution %d  isrc %d  idst %d  iact %d",
		(int) tab->state[sol[ii].isrc][sol[ii].idst].act[sol[ii].iact],
		ii, sol[ii].isrc, sol[ii].idst, sol[ii].iact);
	
	/* reset iact to zero (only becomes non-zero in the branch detection) */
	
	sol[ii].iact = 0;
	
      }
    }
    
    for (ii = 0; ii < nsol; ++ii) {
      ++sol[ii].src;
      ++sol[ii].dst;
      printf ("%s\n%s\n", sol[ii].src, sol[ii].dst);
    }
  }
  
  table_delete (tab);
  
  return 0;
}
