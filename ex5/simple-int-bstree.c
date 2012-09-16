#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <ctype.h>


/* ==================================================
   Binary Search Tree Item
   ================================================== */


typedef struct bsitem_s {
  int data;
  struct bsitem_s * left;
  struct bsitem_s * right;
} BSItem;


/*
 * Helper function to create a new item for a binary search tree. Note
 * that in this simple example, we will never give back the memory
 * allocated here. But any real implementation would need to properly
 * manage its memory, of course.
 */
BSItem * bsitem_new (int data)
{
  BSItem * item;
  if (NULL == (item = calloc (sizeof(*item), 1)))
    err (EXIT_FAILURE, "bsitem_new: malloc");
  item->data = data;
  return item;
}


/* ==================================================
   Binary Search Tree
   ================================================== */


typedef struct bstree_s {
  /*
    It's a bit silly to have a struct which contains just one pointer,
    but a more general implementation of binary search trees will have
    more structure members.
  */
  BSItem * root;
} BSTree;


/*
 * User function to create a new tree. Usually you would have to pass
 * custom functions for deleting data and for comparing data, and
 * there would also be a bstree_delete function to clean up after you
 * are done with the tree. But in this simple example here we skip all
 * of that.
 */
BSTree * bstree_new ()
{
  BSTree * tree;
  if (NULL == (tree = calloc (sizeof(*tree), 1)))
    err (EXIT_FAILURE, "bstree_new: malloc");
  return tree;
}


/*
 * Helper function for inserting an item into a tree. Users will
 * simply call the bstree_ins function instead (without the "_rec"
 * suffix). This function does one of four things:
 *
 *  1. If an empty slot has been found, create a new item for the
 *     data, to attach it as a new leaf to the tree.
 *
 *  2. If the given data is smaller than the one already stored in the
 *     root, then recurse into the left subtree for insertion there.
 *
 *  3. If the data is bigger than what we already have, recurse into
 *     the right subtree instead.
 *
 *  4. Otherwise, the data is already stored in the tree, so we do
 *     nothing.
 *     NOTE that, in a more general setting, if the data compares as
 *     equal to what is stored, it could still be different. In that
 *     case the course of action depends on what is desired of the
 *     tree implementation, but four basic options exist:
 *      a. Ignore the new data and keep the old.
 *      b. Delete the old data, replace it with the new.
 *      c. Treat this as an error.
 *      d. Append the new data to a list stored in the item.
 */
BSItem * bstree_ins_rec (BSTree * tree, BSItem * root, int data)
{
  if (NULL == root)
    return bsitem_new (data);
  
  if (data < root->data)
    root->left = bstree_ins_rec (tree, root->left, data);
  else if (data > root->data)
    root->right = bstree_ins_rec (tree, root->right, data);
  /*
    else ignore: we already have this data
  */
  
  return root;
}


/*
 * User function to insert data (in this simple example that's just a
 * number) into the binary search tree.
 */
void bstree_ins (BSTree * tree, int data)
{
  tree->root = bstree_ins_rec (tree, tree->root, data);
}


/*
 * Helper function for removing an item from the tree. Users will
 * simply call the bstree_rem function instead (without the "_rec"
 * suffix).
 *
 * This function takes the root of a subtree as argument, and returns
 * the item which should replace that subtree. It is intended to be
 * called as follows:
 * \code
 *   tree->root = bstree_rem_rec (tree, tree->root, data);
 * \endcode
 *
 * In most cases, the returned item will be just the root passed in as
 * argument. But if the given root matches the data and one or both of
 * its subtrees are NULL, then something else is returned.  This
 * function does one of the following:
 *
 *  1. If the data is smaller than what is stored in this root,
 *     recurse into the left subtree.
 *
 *  2. If the data is bigger, then recurse to the right.
 *
 *  3. If the data matches and this root is a leaf (has no children),
 *     then simply remove it. NOTE that this is handled transparently
 *     by the code which handles possibility #4.
 *
 *  4. If the data matches and this root has only one subtree (either
 *     left or right), then use the "parent re-attachment trick" to
 *     skip over us.
 *
 *  5. If none of the above can be used, then we find the smallest
 *     child of the right subtree, and replace this root with that
 *     smallest child. It would work just as well to use the biggest
 *     child of the left subtree.
 *
 * NOTE again that we do not properly manage memory in this simple
 * implementation. This function should actually call a user-supplied
 * function to give back the memory used by the, and free the item
 * which gets removed from the tree.
 */
BSItem * bstree_rem_rec (BSTree * tree, BSItem * root, int data)
{
  BSItem *child, *parent;
  
  if (NULL == root)
    return NULL;
  
  if (data < root->data) {
    root->left = bstree_rem_rec (tree, root->left, data);
    return root;
  }
  if (data > root->data) {
    root->right = bstree_rem_rec (tree, root->right, data);
    return root;
  }
  
  /*
   * We have to remove this root. Depending on context, we'll solve
   * this by removing another item after saving its data here.
   */
  
  if (NULL == root->left) {
    /* there is no left subtree: use the "parent re-attachment trick"
       to replace this root with its right subtree (which may be NULL,
       in which case this root was a leaf node) */
    return root->right;
  }
  if (NULL == root->right) {
    /* the other way around is just as easy... */
    return root->left;
  }
  
  /*
   * We have two subtrees, that's slightly trickier: replace this root
   * with the smallest child of its bigger subtree, and remove that
   * smallest child instead.
   */
  
  parent = root;
  child = root->right;
  while (NULL != child->left) {
    parent = child;
    child = child->left;
  }
  root->data = child->data;
  
  /*
    One final potential issue: if root->right has no smaller subtree,
    we have to reattach it's bigger subtree as root->right (same as
    parent->right in this case).
  */
  
  if (parent == root)
    parent->right = child->right;
  else
    parent->left = child->right;
  
  return root;
}


/*
 * User function to actually remove some data. This silently ignore
 * data that is not actually stored in the tree.
 */
void bstree_rem (BSTree * tree, int data)
{
  tree->root = bstree_rem_rec (tree, tree->root, data);
}


/* ==================================================
   Test and Debug
   ================================================== */


typedef enum {
  INSERT,
  REMOVE
} pstate_t;


void print_dot (BSItem * item)
{
  if (NULL != item->left) {
    print_dot (item->left);
    printf ("  \"%d\" -> \"%d\" [label=\"l\"];\n", item->data, item->left->data);
  }
  if (NULL != item->right) {
    printf ("  \"%d\" -> \"%d\" [label=\"r\"];\n", item->data, item->right->data);
    print_dot (item->right);
  }
}


int main (int argc, char ** argv)
{
  int ii;
  pstate_t ps;
  BSTree * tree;
  
  if (2 > argc)
    errx (EXIT_FAILURE, "Please provide a sequence of insertions and removals.");
  
  tree = bstree_new ();
  
  ps = INSERT;
  for (ii = 1; ii < argc; ++ii) {
    if ('I' == toupper(argv[ii][0]))
      ps = INSERT;
    else if ('R' == toupper(argv[ii][0]))
      ps = REMOVE;
    else {
      int num;
      if (1 != sscanf (argv[ii], "%d", &num))
	errx (EXIT_FAILURE, "failed to parse integer from argument %d `%s'", ii, argv[ii]);
      if (INSERT == ps)
	bstree_ins (tree, num);
      else
	bstree_rem (tree, num);
    }
  }
  
  printf ("digraph \"BSTree\" {\n  graph [label=\"%s", argv[1]);
  for (ii = 2; ii < argc; ++ii)
    printf (" %s", argv[ii]);
  printf ("\",overlap=scale];\n");
  print_dot (tree->root);
  printf ("}\n");
  
  return 0;
}
