#include <err.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct item_s {
  int value;
  struct item_s * left;
  struct item_s * right;
} Item;

static Item *root;


Item * insert_rec (Item *parent, int value)
{
  Item *it;
  if (NULL == parent) {
    it = malloc (sizeof *it);
    it->value = value;
    it->left = NULL;
    it->right = NULL;
    return it;
  }
  
  if (value < parent->value) {
    parent->left = insert_rec (parent->left, value);
  }
  else if (value > parent->value) {
    parent->right = insert_rec (parent->right, value);
  }
  
  return parent;
}


void insert (int value)
{
  root = insert_rec (root, value);
}


void dump_rec (Item *parent)
{
  if (NULL == parent)
    return;
  dump_rec (parent->left);
  printf ("  %d", parent->value);
  dump_rec (parent->right);
}


void dump (void)
{
  dump_rec (root);
  printf ("\n");
}


int main (int argc, char **argv)
{
  int ii;
  
  if (2 > argc) {
    fprintf (stderr,
	     "Please provide a sequence of integer values.\n"
	     "For example, give the following command:\n"
	     "  %s 1 2 3 1 2 5 4 3\n",
	     argv[0]);
    return 42;
  }
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, "argument %d `%s' is not an integer", ii, argv[ii]);
    insert (num);
    fprintf (stdout, "inserted %d\n", num);
    dump ();
  }
  
  return 0;
}
