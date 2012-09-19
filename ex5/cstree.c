#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <err.h>


/*
 * Struct to store an item of a child-sibling tree. The data here is
 * just a single character. The struct also has a member called
 * "depth" which should store the depth of the item in the tree (this
 * is computed using the compute_depth function).
 */
typedef struct cs_item_s {
  char data;
  int depth;
  struct cs_item_s *child;
  struct cs_item_s *sibling;
} CSItem;


/*
 * Function to create and initialize a new CSItem.
 */
CSItem * csitem_new (char data)
{
  CSItem * it = calloc (1, sizeof (*it));
  if (NULL == it)
    err (EXIT_FAILURE, "csitem_new: calloc");
  it->data = data;
  return it;
}


/*
 * Function to create a child-sibling tree from a string
 * specification. You don't need to understand this function, but it
 * is a more advanced example of what can be achieved with recursion.
 */
CSItem * cstree_parse (CSItem * parent, const char ** spec)
{
  CSItem *child = NULL;
  
  while ('\0' != **spec){
    
    if (isspace (**spec)) {
      ++(*spec);
      continue;
    }
    
    if (')' == **spec) {
      if (NULL == child)
	errx (EXIT_FAILURE, "cstree_parse: empty sibling list");
      ++(*spec);
      return child;
    }
    
    if (isalnum (**spec)) {
      CSItem *next;
      if (NULL == parent && NULL != child)
	errx (EXIT_FAILURE, "cstree_parse: the root cannot have siblings");
      next = csitem_new (**spec);
      next->sibling = child;
      child = next;
      if (NULL != parent)
	parent->child = child;
      ++(*spec);
      continue;
    }
    
    if ('(' == **spec) {
      if (NULL == child)
	errx (EXIT_FAILURE, "cstree_parse: sibling list without parent");
      ++(*spec);
      cstree_parse (child, spec);
      continue;
    }
    
    errx (EXIT_FAILURE, "cstree_parse: invalid character `%c'", **spec);
  }
  
  if (NULL == child)
    errx (EXIT_FAILURE, "cstree_parse: empty root sibling list or unbalanced parenthesis");
  
  return child;
}


/*
 * A function to give back the memory used by all the items in a
 * child-sibling tree.
 */
void cstree_free (CSItem * item)
{
  CSItem * child;
  for (child = item->child; NULL != child; child = child->sibling)
    cstree_free (child);
  free (item);
}


/*
 * **************************************************
 * * IMPLEMENT THIS FUNCTION ************************
 * **************************************************
 *
 * A function to iterate over all the items in the tree, using
 * post-order traversal. In other words, you should first recurse into
 * all children of the given item, and then print the data of the
 * item.
 */
void cstree_post_order (CSItem * item)
{
  printf ("*** Please implement cstree_compute_depth.\n");
  
  /*
    First, iterate over all children of this item, and recursively
    call cstree_post_order on them. Hint: look at cstree_free for an
    example of how to iterate over all children.
  */
  
  /*
    Then, print the data of this item on a line by itself, and indent
    the output by two spaces for each level of depth. Like this:
    
    for (ii = 0; ii < item->depth; ++ii)
      printf (" ");
    printf ("%c\n", item->data);
  */
}


/*
 * **************************************************
 * * IMPLEMENT THIS FUNCTION ************************
 * **************************************************
 *
 * A function to compute the depth of an item, and all of its children
 * (and their children and so forth). When called on the root of a
 * child-sibling tree, you have to pass -1 as parent_depth so that the
 * root gets assigned zero depth.
 */
void cstree_compute_depth (CSItem * item, int parent_depth)
{
  printf ("*** Please implement cstree_compute_depth.\n");
}


/*
 * **************************************************
 * * IMPLEMENT THIS FUNCTION ************************
 * **************************************************
 *
 * A function just like cstree_post_order, but using post-order
 * traversal instead. In other words, first print the data of the
 * given item, then recursively call cstree_pre_order on its children.
 */
void cstree_pre_order (CSItem * item)
{
  printf ("*** Please implement cstree_pre_order.\n");
}


int main (int argc, char ** argv)
{
  CSItem * root;
  const char * spec = "A(E(7(zyx))D(6543)CB(21))";
  
  printf ("initializing tree\n");
  root = cstree_parse (NULL, &spec);
  
  printf ("computing depth\n");
  cstree_compute_depth (root, -1);
  
  printf ("post-order traversal:\n");
  cstree_post_order (root);
  
  printf ("pre-order traversal:\n");
  cstree_pre_order (root);
  
  cstree_free (root);
  return 0;
}
