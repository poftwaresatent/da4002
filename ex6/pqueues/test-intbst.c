#include "intbst.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define BUFSIZE 1024


typedef enum {
  INSERT,
  REMOVE
} pstate_t;


static void printitem (IntBST * item, void * foo)
{
  printf ("  %d", item->data);
}


int main (int argc, char ** argv)
{
  int ii;
  pstate_t ps;
  IntBST * root;
  char buf[BUFSIZE];
  char * label;
  int nremain, nwritten;
  
  if (2 > argc)
    errx (EXIT_FAILURE,
	  "Please provide a sequence of insertions and removals.\n"
	  "For example, give the following command:\n"
	  "  %s 4 2 6 1 3 5 7",
	  argv[0]);
  
  root = NULL;
  ps = INSERT;
  for (ii = 1; ii < argc; ++ii) {
    if ('i' == argv[ii][0])
      ps = INSERT;
    else if ('r' == argv[ii][0])
      ps = REMOVE;
    else {
      int num;
      if (1 != sscanf (argv[ii], "%d", &num))
	errx (EXIT_FAILURE, "failed to parse integer from argument %d `%s'", ii, argv[ii]);
      if (INSERT == ps) {
	printf ("inserting %d\n", num);
	if (NULL == root)
	  root = intbst_new (num);
	else
	  root = intbst_ins (root, num);
	intbst_in_order (root, printitem, NULL);
	printf ("\n");
      }
      else {
	printf ("removing %d\n", num);
	if (NULL == root)
	  errx (EXIT_FAILURE, __FILE__": %s: cannot remove items from NULL tree", __func__);
	root = intbst_rem (root, num);
	intbst_in_order (root, printitem, NULL);
	printf ("\n");
      }
    }
  }
  
  nremain = BUFSIZE;
  label = buf;
  nwritten = snprintf (label, nremain, "IntBST '%s", argv[1]);
  if (0 > nwritten || nremain <= 0)
    errx (EXIT_FAILURE, __FILE__": %s: error creating label string", __func__);
  label += nwritten;
  nremain -= nwritten;
  for (ii = 2; ii < argc; ++ii) {
    nwritten = snprintf (label, nremain, " %s", argv[ii]);
    if (0 > nwritten || nremain <= 0)
      errx (EXIT_FAILURE, __FILE__": %s: error creating label string", __func__);
    label += nwritten;
    nremain -= nwritten;
  }
  nwritten = snprintf (label, nremain, "'");
  if (0 > nwritten || nremain <= 0)
    errx (EXIT_FAILURE, __FILE__": %s: error creating label string", __func__);
  label = buf;
  
  intbst_print_dot (root, "dump-intbst.dot", label);
  
  intbst_free (root);
  return 0;
}
