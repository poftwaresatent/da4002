#include <err.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct item_s {
  int xval, yval;
  struct item_s *xnext, *ynext;
} Item;

static Item *xhead;
static Item *yhead;

void insert (int xval, int yval)
{
  Item *it = malloc (sizeof *it);
  it->xval = xval;
  it->yval = yval;
  if (NULL == xhead) {
    xhead = it;
    yhead = it;
    it->xnext = NULL;
    it->ynext = NULL;
  }
  else {
    Item *pp, *nn;
    pp = 0;
    nn = xhead;
    while (NULL != nn && xval > nn->xval) {
      pp = nn;
      nn = nn->xnext;
    }
    if (NULL == pp) {
      it->xnext = xhead;
      xhead = it;
    }
    else {
      it->xnext = nn;
      pp->xnext = it;
    }
    pp = 0;
    nn = yhead;
    while (NULL != nn && yval > nn->yval) {
      pp = nn;
      nn = nn->ynext;
    }
    if (NULL == pp) {
      it->ynext = yhead;
      yhead = it;
    }
    else {
      it->ynext = nn;
      pp->ynext = it;
    }
  }
}


void xdump (void)
{
  printf ("X:");
  if (NULL == xhead) {
    printf ("  EMPTY\n");
  }
  else {
    Item *it;
    for (it = xhead; it != NULL; it = it->xnext) {
      printf ("  (%d, %d)", it->xval, it->yval);
    }
    printf ("\n");
  }
}


void ydump (void)
{
  printf ("Y:");
  if (NULL == yhead) {
    printf ("  EMPTY\n");
  }
  else {
    Item *it;
    for (it = yhead; it != NULL; it = it->ynext) {
      printf ("  (%d, %d)", it->xval, it->yval);
    }
    printf ("\n");
  }
}


int main (int argc, char **argv)
{
  int ii;
  
  if (3 > argc) {
    fprintf (stderr,
	     "Please provide a sequence of 2N integer values.\n"
	     "For example, give the following command:\n"
	     "  %s 1 4   4 3   3 2   0 1   2 0\n",
	     argv[0]);
    return 42;
  }
  
  for (ii = 1; ii < argc - 1; ii += 2) {
    int xx, yy;
    if (1 != sscanf (argv[ii], "%d", &xx))
      errx (EXIT_FAILURE, "argument %d `%s' is not an integer", ii, argv[ii]);
    if (1 != sscanf (argv[ii+1], "%d", &yy))
      errx (EXIT_FAILURE, "argument %d `%s' is not an integer", ii+1, argv[ii+1]);
    insert (xx, yy);
    fprintf (stdout, "inserted (%d, %d)\n", xx, yy);
    xdump ();
    ydump ();
  }
  
  return 0;
}
