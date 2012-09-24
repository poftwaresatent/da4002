#include "intmbst.h"
#include <stdio.h>
#include <err.h>
#include <stdlib.h>


IntMBst * intmbst_new (int data)
{
  IntMBst * root;
  if (NULL == (root = calloc (1, sizeof(*root))))
    err (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  root->dvec = intvec_new (1);
  intvec_ins (root->dvec, root->dvec->len, data);
  return root;
}


void intmbst_delete (IntMBst * root)
{
  if (NULL == root)
    return;
  intmbst_delete (root->left);
  intmbst_delete (root->right);
  intvec_delete (root->dvec);
  free (root);
}


IntMBst * intmbst_find (IntMBst * root, int data, IntMBst ** parent)
{
  if (NULL != parent)
    *parent = NULL;
  
  while (NULL != root) {
    if (data < root->dvec->arr[0]) {
      if (NULL != parent)
	*parent = root;
      root = root->left;
    }
    else if (data > root->dvec->arr[0]) {
      if (NULL != parent)
	*parent = root;
      root = root->right;
    }
    else
      return root;
  }
  
  return NULL;
}


IntMBst * intmbst_ins (IntMBst * root, int data)
{
  if (NULL == root)
    return intmbst_new (data);
  
  if (data < root->dvec->arr[0])
    root->left = intmbst_ins (root->left, data);
  else if (data > root->dvec->arr[0])
    root->right = intmbst_ins (root->right, data);
  else				/* append to existing item with matching key */
    intvec_ins (root->dvec, root->dvec->len, data);
  
  return root;
}


IntMBst * intmbst_rem (IntMBst * root, int data)
{
  IntMBst *child, *parent;
  
  if (NULL == root)
    return NULL;
  
  if (data < root->dvec->arr[0]) {
    root->left = intmbst_rem (root->left, data);
    return root;
  }
  if (data > root->dvec->arr[0]) {
    root->right = intmbst_rem (root->right, data);
    return root;
  }
  
  /*
   * Data matches this root, remove one from our vector. In this case,
   * we "throw away" the result because all matching data are actually
   * the same. In more relaistic settings, we'd have to return one of
   * the matching data, but keep the others around (that needs a
   * change to this function's return type, too).
   */
  
  intvec_rem (root->dvec, root->dvec->len - 1);
  if (0 < root->dvec->len)
    return root;
  
  /*
   * We have to remove this root. Depending on context, we'll solve
   * this by removing another item after saving its data here.
   */
  
  if (NULL == root->left) {
    /* there is no left subtree: use the "parent re-attachment trick"
       to replace this root with its right subtree (which may be NULL,
       in which case this root was a leaf node) */
    IntMBst *tmp = root->right;
    intmbst_delete (root);
    return tmp;
  }
  if (NULL == root->right) {
    /* the other way around is just as easy... */
    IntMBst *tmp = root->left;
    intmbst_delete (root);
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
  intvec_delete (root->dvec);
  root->dvec = child->dvec;
  child->dvec = NULL;		/* to avoid double-free when we delete the child node */
  
  /*
    One final potential issue: if root->right has no smaller subtree,
    we have to reattach it's bigger subtree as root->right (same as
    parent->right in this case).
  */
  
  if (parent == root)
    parent->right = child->right;
  else
    parent->left = child->right;
  intmbst_delete (child);
  
  return root;
}


IntMBst * intmbst_rem_max (IntMBst * root, int * maxdata)
{
  IntMBst *parent, *child;
  
  if (NULL == root)
    return NULL;
  
  child = root;
  parent = NULL;
  while (NULL != child->right) {
    parent = child;
    child = child->right;
  }
  
  *maxdata = intvec_rem (child->dvec, child->dvec->len - 1);
  if (0 < child->dvec->len)
    return root;
  
  if (NULL == parent)
    root = child->left;
  else
    parent->right = child->left;
  
  child->left = NULL;
  intmbst_delete (child);
  
  return root;
}


void intmbst_in_order (IntMBst * root, intmbst_visit_fct_t fct, void * arg)
{
  if (NULL == root)
    return;
  intmbst_in_order (root->left, fct, arg);
  fct (root, arg);
  intmbst_in_order (root->right, fct, arg);
}


static void print_dot_ (IntMBst * item, FILE * of)
{
  if (NULL != item->left) {
    print_dot_ (item->left, of);
    fprintf (of, "  \"%d\" -> \"%d\" [label=\"l\"];\n", item->dvec->arr[0], item->left->dvec->arr[0]);
  }
  if (NULL != item->right) {
    fprintf (of, "  \"%d\" -> \"%d\" [label=\"r\"];\n", item->dvec->arr[0], item->right->dvec->arr[0]);
    print_dot_ (item->right, of);
  }
}


int intmbst_print_dot (IntMBst * root, const char * filename, const char * label)
{
  FILE * of;
  
  if (NULL == (of = fopen (filename, "w")))
    return -1;
  
  if (label)
    fprintf (of, "digraph \"IntMBst\" {\n  graph [label=\"%s\",overlap=scale];\n", label);
  else
    fprintf (of, "digraph \"IntMBst\" {\n  graph [overlap=scale];\n");
  print_dot_ (root, of);
  fprintf (of, "}\n");
  
  return fclose (of);
}
