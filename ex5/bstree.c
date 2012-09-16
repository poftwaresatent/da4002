#include <stdio.h>
#include <err.h>
#include <stdlib.h>


/* ==================================================
   Binary Search Tree Item
   ================================================== */


typedef struct bsitem_s {
  void * data;
  struct bsitem_s * smaller;
  struct bsitem_s * bigger;
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
  bsitem_delete_rec (item->smaller, data_delete);
  bsitem_delete_rec (item->bigger, data_delete);
  if (NULL != data_delete)
    data_delete (item->data);
  free (item);
}


void bsitem_app_io_rec (BSItem * item, void (*fct)(void*))
{
  if (NULL == item)
    return;
  bsitem_app_io_rec (item->smaller, fct);
  fct (item->data);
  bsitem_app_io_rec (item->bigger, fct);
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
    root->smaller = bstree_ins_rec (tree, root->smaller, data);
  else if (0 < cmp)		/* it's bigger than our data */
    root->bigger = bstree_ins_rec (tree, root->bigger, data);
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
    root->smaller = bstree_rem_rec (tree, root->smaller, data);
    return root;
  }
  if (0 < cmp) {
    /* remove it from the bigger subtree */
    root->bigger = bstree_rem_rec (tree, root->bigger, data);
    return root;
  }
  
  /*
    root matches the data, thus remove "this" item (we may end up
    replacing our data and removing another one, depending on context)
  */
  
  if (NULL != tree->data_delete) {
    tree->data_delete (root->data);
  }
  
  if (NULL == root->smaller) {
    /* easy: there is no smaller subtree, use the "parent
       re-attachment trick" (replace this root with its bigger
       subtree, which may be NULL here by the way) */
    BSItem *tmp;
    tmp = root->bigger;
    free (root);
    return tmp;
  }
  if (NULL == root->bigger) {
    /* the other way around is just as easy... */
    BSItem *tmp;
    tmp = root->smaller;
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
  child = root->bigger;
  while (NULL != child->smaller) {
    parent = child;
    child = child->smaller;
  }
  root->data = child->data;
  
  /* one final potential issue: if root->bigger has no smaller
     subtree, we have to reattach it's bigger subtree as
     root->bigger  */
  if (parent == root)
    parent->bigger = child->bigger;
  else
    parent->smaller = child->bigger;
  
  free (child);
  
  return root;
}


void bstree_rem (BSTree * tree, void * data)
{
  tree->root = bstree_rem_rec (tree, tree->root, data);
}


void bstree_app_io (BSTree * tree, void (*fct)(void*))
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


void int_print (void * data)
{
  printf ("%d\n", *(int*)data);
}


int main (int argc, char ** argv)
{
  int foo[] = { 1, 2, 9, 4, 6, 3, 3, 7, 0, 2 };
  int ii;
  BSTree * tree;

  tree = bstree_new (int_cmp, free);
  for (ii = 0; ii < sizeof(foo)/sizeof(*foo); ++ii) {
    int *dup;
    if (NULL == (dup = malloc (sizeof(*dup))))
      err (EXIT_FAILURE, "main: malloc");
    *dup = foo[ii];
    bstree_ins (tree, dup);
  }
  
  bstree_app_io (tree, int_print);
  
  bstree_delete (tree);
  return 0;
}
