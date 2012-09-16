#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <ctype.h>


/* ==================================================
   Binary Search Tree Item
   ================================================== */


typedef struct bsitem_s {
  void * data;
  struct bsitem_s * left;
  struct bsitem_s * right;
} BSItem;


BSItem * bsitem_new (void * data)
{
  BSItem * item;
  if (NULL == (item = calloc (sizeof(*item), 1)))
    err (EXIT_FAILURE, "bsitem_new: malloc");
  item->data = data;
  return item;
}


void bsitem_delete_rec (BSItem * item, void (*data_delete)(void*))
{
  if (NULL == item)
    return;
  bsitem_delete_rec (item->left, data_delete);
  bsitem_delete_rec (item->right, data_delete);
  if (NULL != data_delete)
    data_delete (item->data);
  free (item);
}


void bsitem_app_io_rec (BSItem * item, void (*fct)(BSItem*))
{
  if (NULL == item)
    return;
  bsitem_app_io_rec (item->left, fct);
  fct (item);
  bsitem_app_io_rec (item->right, fct);
}


/* ==================================================
   Binary Search Tree
   ================================================== */


typedef struct bstree_s {
  unsigned int size;
  BSItem * root;
  int (*data_cmp)(void*, void*);
  void (*data_delete)(void*);
} BSTree;


BSTree * bstree_new (int (*data_cmp)(void*, void*), void (*data_delete)(void*))
{
  BSTree * tree;
  if (NULL == (tree = calloc (sizeof(*tree), 1)))
    err (EXIT_FAILURE, "bstree_new: malloc");
  tree->data_cmp = data_cmp;
  tree->data_delete = data_delete;
  return tree;
}


void bstree_delete (BSTree * tree)
{
  if (NULL != tree->root) {
    bsitem_delete_rec (tree->root, tree->data_delete);
    tree->root = NULL;
  }
  free (tree);
}


BSItem * bstree_ins_rec (BSTree * tree, BSItem * root, void * data)
{
  int cmp;
  
  if (NULL == root)
    return bsitem_new (data);
  
  cmp = tree->data_cmp(data, root->data);
  if (0 > cmp)			/* it's smaller than our data */
    root->left = bstree_ins_rec (tree, root->left, data);
  else if (0 < cmp)		/* it's bigger than our data */
    root->right = bstree_ins_rec (tree, root->right, data);
  else {			/* it's equal to our data */
    if (NULL != tree->data_delete)
      tree->data_delete (root->data);
    root->data = data;
  }
  
  return root;
}


void bstree_ins (BSTree * tree, void * data)
{
  tree->root = bstree_ins_rec (tree, tree->root, data);
}


BSItem * bstree_rem_rec (BSTree * tree, BSItem * root, void * data)
{
  int cmp;
  
  if (NULL == root)
    return NULL;
  
  cmp = tree->data_cmp(data, root->data);
  if (0 > cmp) {
    /* remove it from the smaller subtree */
    root->left = bstree_rem_rec (tree, root->left, data);
    return root;
  }
  if (0 < cmp) {
    /* remove it from the bigger subtree */
    root->right = bstree_rem_rec (tree, root->right, data);
    return root;
  }
  
  /*
    root matches the data, thus remove "this" item (we may end up
    replacing our data and removing another one, depending on context)
  */
  
  if (NULL != tree->data_delete) {
    tree->data_delete (root->data);
  }
  
  if (NULL == root->left) {
    /* easy: there is no smaller subtree, use the "parent
       re-attachment trick" (replace this root with its bigger
       subtree, which may be NULL here by the way) */
    BSItem *tmp;
    tmp = root->right;
    free (root);
    return tmp;
  }
  if (NULL == root->right) {
    /* the other way around is just as easy... */
    BSItem *tmp;
    tmp = root->left;
    free (root);
    return tmp;
  }
  
  /*
    this root has two subtrees, which is trickier... we replace its
    data with the smallest child of its bigger subtree, and remove
    that smallest child instead (the other way around would work as
    well, using the biggest child of the smaller subtree).
  */
  BSItem *child, *parent;
  parent = root;
  child = root->right;
  while (NULL != child->left) {
    parent = child;
    child = child->left;
  }
  root->data = child->data;
  
  /* one final potential issue: if root->right has no smaller subtree,
     we have to reattach it's bigger subtree as root->right (same as
     parent->right in this case) */
  if (parent == root)
    parent->right = child->right;
  else
    parent->left = child->right;
  
  free (child);
  
  return root;
}


void bstree_rem (BSTree * tree, void * data)
{
  tree->root = bstree_rem_rec (tree, tree->root, data);
}


void bstree_app_io (BSTree * tree, void (*fct)(BSItem*))
{
  bsitem_app_io_rec (tree->root, fct);
}


/* ==================================================
   Test and Debug
   ================================================== */


int int_cmp (void * lhs, void * rhs)
{
  return *(int*)lhs - *(int*)rhs;
}


void int_item_print_dot (BSItem * item)
{
  if (NULL != item->left)
    printf ("  \"%d\" -> \"%d\" [label=\"l\"];\n", *(int*)item->data, *(int*)item->left->data);
  if (NULL != item->right)
    printf ("  \"%d\" -> \"%d\" [label=\"r\"];\n", *(int*)item->data, *(int*)item->right->data);
}


typedef enum {
  INSERT,
  REMOVE
} pstate_t;


int main (int argc, char ** argv)
{
  int ii;
  pstate_t ps;
  BSTree * tree;
  
  if (2 > argc)
    errx (EXIT_FAILURE, "Please provide a sequence of insertions and removals.");
  
  tree = bstree_new (int_cmp, free);
  
  ps = INSERT;
  for (ii = 1; ii < argc; ++ii) {
    if ('I' == toupper(argv[ii][0]))
      ps = INSERT;
    else if ('R' == toupper(argv[ii][0]))
      ps = REMOVE;
    else {
      int *num;
      if (NULL == (num = malloc (sizeof(*num))))
	err (EXIT_FAILURE, "failed to allocate integer");
      if (1 != sscanf (argv[ii], "%d", num))
	errx (EXIT_FAILURE, "failed to parse integer from argument %d `%s'", ii, argv[ii]);
      if (INSERT == ps)
	bstree_ins (tree, num);
      else {
	bstree_rem (tree, num);
	free (num);
      }
    }
  }
  
  printf ("digraph \"BSTree\" {\n  graph [label=\"%s", argv[1]);
  for (ii = 2; ii < argc; ++ii)
    printf (" %s", argv[ii]);
  printf ("\",overlap=scale];\n");
  bstree_app_io (tree, int_item_print_dot);
  printf ("}\n");
  
  bstree_delete (tree);
  return 0;
}
