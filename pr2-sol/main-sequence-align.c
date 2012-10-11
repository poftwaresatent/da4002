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
  int buflen;
  char *srcbuf, *src;
  char *dstbuf, *dst;
  int isrc, idst, iact;
  struct {
    int id, orig, isrc, idst, iact;
  } meta;
} Alignment;


static int meta_id = 0;

Alignment * alignment_new (Table * tab)
{
  Alignment *al;
  
  if (NULL == (al = malloc (sizeof *al)))
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  
  al->buflen = tab->srclen + tab->dstlen + 1;
  if (NULL == (al->srcbuf = calloc (al->buflen, sizeof(char))))
    err (EXIT_FAILURE, __FILE__": %s: calloc srcbuf", __func__);
  al->src = al->srcbuf + al->buflen;
  
  if (NULL == (al->dstbuf = calloc (al->buflen, sizeof(char))))
    err (EXIT_FAILURE, __FILE__": %s: calloc dstbuf", __func__);
  al->dst = al->dstbuf + al->buflen;
  
  al->isrc = tab->srclen;
  al->idst = tab->dstlen;
  al->iact = 0;
  
  al->meta.id = meta_id++;
  al->meta.orig = al->meta.id;
  al->meta.isrc = al->isrc;
  al->meta.idst = al->idst;
  al->meta.iact = al->iact;
  
  return al;
}


void alignment_dup (Alignment * clone, Alignment const * orig, int iact)
{
  memcpy (clone, orig, sizeof *clone);
  
  if (NULL == (clone->srcbuf = malloc (clone->buflen * sizeof(char))))
    err (EXIT_FAILURE, __FILE__": %s: malloc srcbuf", __func__);
  memcpy (clone->srcbuf, orig->srcbuf, clone->buflen * sizeof(char));
  printf ("  wtf srcbuf: ");
  int wtf;
  for (wtf = 0; wtf < clone->buflen; ++wtf)
    printf (clone->srcbuf[wtf] == orig->srcbuf[wtf] ? "." : "X");
  printf ("\n");
  clone->src = clone->srcbuf + (orig->src - orig->srcbuf);
  
  if (NULL == (clone->dstbuf = malloc (clone->buflen * sizeof(char))))
    err (EXIT_FAILURE, __FILE__": %s: malloc dstbuf", __func__);
  memcpy (clone->dstbuf, orig->dstbuf, clone->buflen * sizeof(char));
  printf ("  wtf dstbuf: ");
  for (wtf = 0; wtf < clone->buflen; ++wtf)
    printf (clone->dstbuf[wtf] == orig->dstbuf[wtf]
	    ? (orig->dstbuf[wtf] == '\0' ? "0" : ".")
	    : "X");
  printf ("\n");
  clone->dst = clone->dstbuf + (orig->dst - orig->dstbuf);
  
  clone->iact = iact;

  clone->meta.id = meta_id++;
  clone->meta.orig = orig->meta.id;
  clone->meta.isrc = orig->isrc;
  clone->meta.idst = orig->idst;
  clone->meta.iact = iact;
  
  printf ("  dup: orig:  buflen %d  id %d  orig %d  isrc %d  idst %d  iact %d\n"
	  "       clone: buflen %d  id %d  orig %d  isrc %d  idst %d  iact %d\n"
	  "       orig  src: %s\n"
	  "       clone src: %s\n"
	  "       orig  dst: %s\n"
	  "       clone dst: %s\n\n",
	  orig->buflen, orig->meta.id, orig->meta.orig, orig->meta.isrc, orig->meta.idst, orig->meta.iact,
	  clone->buflen, clone->meta.id, clone->meta.orig, clone->meta.isrc, clone->meta.idst, clone->meta.iact,
	  orig->src, clone->src, orig->dst, clone->dst);
}


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
  Alignment *sol;
  int nsol = 1;
  int done;
  
  if (argc < 3)
    errx (EXIT_FAILURE, "please provide two strings on the command line");
  tab = table_new (argv[1], argv[2]);
  
  printf ("input source:      %s\n"
	  "input destination: %s\n",
	  argv[1], argv[2]);
  
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
  
  sol = alignment_new (tab);
  
  for (done = 0; done != 1; /**/) {
    int ncheck;
    done = 1;
    
    /*
      check for branches, but may end up appending duplicates which
      should not be checked this time around... so remember the old
      size in ncheck
    */
    ncheck = nsol;
    for (ii = 0; ii < ncheck; ++ii) {
      
      /*
	skip finished alignments
      */
      if (sol[ii].isrc == 0 && sol[ii].idst == 0)
	continue;
      
      /*
	check whether we have a 2nd and a 3rd action
      */
      for (jj = 1; jj <= 2; ++jj) {
	
	/*
	  no more actions when we hit the '\0' of the action string
	*/
	if (tab->state[sol[ii].isrc][sol[ii].idst].act[jj] == '\0')
	  break;
	
	/*
	  append a duplicate of sol[ii] that uses jj as iact
	*/
	if (NULL == (sol = realloc (sol, (nsol + 1) * sizeof *sol)))
	  err (EXIT_FAILURE, "realloc sol");
	alignment_dup (sol + nsol, sol + ii, jj);
	
	++nsol;
      }
    }
    
    /*
      update all alignment branches
    */
    for (ii = 0; ii < nsol; ++ii) {
      char act;
      
      /*
	skip finished alignments
      */
      if (sol[ii].isrc == 0 && sol[ii].idst == 0)
	continue;
      
      /*
	perform next action in the backtrace
      */
      done = 0;
      act = tab->state[sol[ii].isrc][sol[ii].idst].act[sol[ii].iact];
      if ('m' == act) {
	*(--sol[ii].src) = tab->src[--sol[ii].isrc];
	*(--sol[ii].dst) = tab->dst[--sol[ii].idst];
      }
      else if ('i' == act) {
	*(--sol[ii].src) = '_';
	*(--sol[ii].dst) = tab->dst[--sol[ii].idst];
      }
      else if ('d' == act) {
	*(--sol[ii].src) = tab->src[--sol[ii].isrc];
	*(--sol[ii].dst) = '_';
      }
      else
	errx (EXIT_FAILURE, "BUG: action %d  solution %d  isrc %d  idst %d  iact %d",
	      (int) act, ii, sol[ii].isrc, sol[ii].idst, sol[ii].iact);
      
      /*
	reset iact to zero (only becomes non-zero in the branch detection)
      */
      sol[ii].iact = 0;
    }
  }
  
  /*
    print all optimal alignments
  */
  printf ("backtrace:\n\n");
  for (ii = 0; ii < nsol; ++ii)
    printf ("output source:      %s\n"
	    "output destination: %s\n"
	    "  meta: id %d  orig %d  isrc %d  idst %d iact %d\n\n",
	    sol[ii].src, sol[ii].dst,
	    sol[ii].meta.id, sol[ii].meta.orig, sol[ii].meta.isrc, sol[ii].meta.idst, sol[ii].meta.iact);
  
  /***************************************************
   * clean up after ourselves
   */
  
  for (ii = 0; ii < nsol; ++ii) {
    free (sol[ii].srcbuf);
    free (sol[ii].dstbuf);
  }
  free (sol);
  table_delete (tab);
  
  return 0;
}
