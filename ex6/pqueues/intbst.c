#include "intbst.h"
#include <stdio.h>
#include <err.h>
#include <stdlib.h>


IntBST * intbst_new (int data)
{
  IntBST * root;
  if (NULL == (root = calloc (1, sizeof(*root))))
    err (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  root->data = data;
  return root;
}


void intbst_free (IntBST * root)
{
  if (NULL == root)
    return;
  intbst_free (root->left);
  intbst_free (root->right);
  free (root);
}


IntBST * intbst_find (IntBST * root, int data, IntBST ** parent)
{
  if (NULL != parent)
    *parent = NULL;
  
  while (NULL != root) {
    if (data < root->data) {
      if (NULL != parent)
	*parent = root;
      root = root->left;
    }
    else if (data > root->data) {
      if (NULL != parent)
	*parent = root;
      root = root->right;
    }
    else
      return root;
  }
  
  return NULL;
}


IntBST * intbst_ins (IntBST * root, int data)
{
  if (NULL == root)
    return intbst_new (data);
  
  if (data < root->data)
    root->left = intbst_ins (root->left, data);
  else if (data > root->data)
    root->right = intbst_ins (root->right, data);
  /*
    else ignore: we already have this data
  */
  
  return root;
}


IntBST * intbst_rem (IntBST * root, int data)
{
  IntBST *child, *parent;
  
  if (NULL == root)
    return NULL;
  
  if (data < root->data) {
    root->left = intbst_rem (root->left, data);
    return root;
  }
  if (data > root->data) {
    root->right = intbst_rem (root->right, data);
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
    IntBST *tmp = root->right;
    free (root);
    return tmp;
  }
  if (NULL == root->right) {
    /* the other way around is just as easy... */
    IntBST *tmp = root->left;
    free (root);
    return tmp;
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
  free (child);
  
  return root;
}


void intbst_in_order (IntBST * root, intbst_visit_fct_t fct, void * arg)
{
  if (NULL == root)
    return;
  intbst_in_order (root->left, fct, arg);
  fct (root, arg);
  intbst_in_order (root->right, fct, arg);
}


static void print_dot_ (IntBST * item, FILE * of)
{
  if (NULL != item->left) {
    print_dot_ (item->left, of);
    fprintf (of, "  \"%d\" -> \"%d\" [label=\"l\"];\n", item->data, item->left->data);
  }
  if (NULL != item->right) {
    fprintf (of, "  \"%d\" -> \"%d\" [label=\"r\"];\n", item->data, item->right->data);
    print_dot_ (item->right, of);
  }
}


int intbst_print_dot (IntBST * root, const char * filename, const char * label)
{
  FILE * of;
  
  if (NULL == (of = fopen (filename, "w")))
    return -1;
  
  if (label)
    fprintf (of, "digraph \"IntBST\" {\n  graph [label=\"%s\",overlap=scale];\n", label);
  else
    fprintf (of, "digraph \"IntBST\" {\n  graph [overlap=scale];\n");
  print_dot_ (root, of);
  fprintf (of, "}\n");
  
  return fclose (of);
}
