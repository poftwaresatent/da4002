#include <stdio.h>
#include <err.h>
#include <stdlib.h>


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
  
  fprintf (stderr, "bsitem_new         i: %p  d: %p  (%d)\n", item, data, *(int*)data);
  
  return item;
}


void bsitem_delete_rec (BSItem * item, void (*data_delete)(void*))
{
  if (item->smaller)
    bsitem_delete_rec (item->smaller, data_delete);
  if (item->smaller)
    bsitem_delete_rec (item->smaller, data_delete);
  
  fprintf (stderr, "bsitem_delete_rec  i: %p  d: %p  (%d)\n",
	   item, item->data, *(int*)(item->data));
  
  if (NULL != data_delete)
    data_delete (item->data);
  free (item);
}


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
  if (NULL == root) {
    return bsitem_new (data);
  }
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



int int_cmp (void * lhs, void * rhs)
{
  return *(int*)lhs - *(int*)rhs;
}


void int_fake_delete (void * ptr)
{
  fprintf (stderr, "would free                         d: %p   %d\n", ptr, *(int*)ptr);
}


int main (int argc, char ** argv)
{
  int foo[] = { 1, 2 };//, 9 };//, 4, 6, 3, 3, 7, 0, 2 };
  int ii;
  BSTree * tree = bstree_new (int_cmp, int_fake_delete);
  for (ii = 0; ii < sizeof(foo)/sizeof(*foo); ++ii)
    bstree_ins (tree, foo+ii);
  bstree_delete (tree);
  return 0;
}
