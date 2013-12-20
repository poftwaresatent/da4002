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


void pdot_r (Item * parent)
{
  if (parent->left) {
    pdot_r (parent->left);
    printf ("  \"%d\" -> \"%d\" [label=\"l\"];\n", parent->value, parent->left->value);
  }
  if (parent->right) {
    printf ("  \"%d\" -> \"%d\" [label=\"r\"];\n", parent->value, parent->right->value);
    pdot_r (parent->right);
  }
}


void pdot ()
{
  printf ("digraph \"bstree\" {\n  graph [overlap=scale];\n");
  pdot_r (root);
  printf ("}\n");
  
}


void dump_in_order (Item *parent)
{
  if (NULL == parent) {
    return;
  }
  dump_in_order (parent->left);
  fprintf (stderr, "  %d", parent->value);
  dump_in_order (parent->right);
}


void dump_pre_order (Item *parent)
{
  if (NULL == parent) {
    return;
  }
  fprintf (stderr, "  %d", parent->value);
  dump_pre_order (parent->left);
  dump_pre_order (parent->right);
}


void dump_post_order (Item *parent)
{
  if (NULL == parent) {
    return;
  }
  dump_post_order (parent->left);
  dump_post_order (parent->right);
  fprintf (stderr, "  %d", parent->value);
}


typedef struct list_item_s {
  Item * item;
  struct list_item_s * next;
} ListItem;

static ListItem *head, *tail;


void queue_init (void)
{
  head = NULL;
  tail = NULL;
}


void queue_push (Item * item)
{
  ListItem * li = malloc (sizeof (ListItem));
  li->item = item;
  li->next = NULL;
  if (head == NULL) {
    head = li;
  }
  else {
    tail->next = li;
  }
  tail = li;
}


Item * queue_pop ()
{
  ListItem * tmp = head;
  Item * it;
  if (tmp == NULL) {
    return NULL;
  }
  it = tmp->item;
  head = tmp->next;
  if (head == NULL) {
    tail = NULL;
  }
  free (tmp);
  return it;
}


void dump_level_order (Item *parent)
{
  Item * it;
  if (NULL == parent) {
    return;
  }
  queue_init();
  queue_push (parent);
  for (it = queue_pop(); it != NULL; it = queue_pop()) {
    fprintf (stderr, "  %d", it->value);
    if (it->left) {
      queue_push (it->left);
    }
    if (it->right) {
      queue_push (it->right);
    }
  }
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
    fprintf (stderr, "inserted %d\n", num);
  }
  
  fprintf (stderr, "pre-order:\n");
  dump_pre_order (root);
  fprintf (stderr, "\npost-order:\n");
  dump_post_order (root);
  fprintf (stderr, "\nin-order:\n");
  dump_in_order (root);
  fprintf (stderr, "\nlevel-order:\n");
  dump_level_order (root);
  fprintf (stderr, "\n");
  
  pdot();
  
  return 0;
}
