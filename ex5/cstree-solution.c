#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <err.h>


typedef struct cs_item_s {
  char data;
  int depth;
  struct cs_item_s *child;
  struct cs_item_s *sibling;
} CSItem;


CSItem * csitem_new (char data)
{
  CSItem * it = calloc (1, sizeof (*it));
  if (NULL == it)
    err (EXIT_FAILURE, "csitem_new: calloc");
  it->data = data;
  return it;
}


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


void cstree_compute_depth (CSItem * item, int parent_depth)
{
  item->depth = ++parent_depth;
  for (item = item->child; NULL != item; item = item->sibling)
    cstree_compute_depth (item, parent_depth);
}


void cstree_pre_order (CSItem * item)
{
  int ii;
  for (ii = 0; ii < item->depth; ++ii)
    printf ("  ");
  printf ("%c\n", item->data);
  for (item = item->child; NULL != item; item = item->sibling)
    cstree_pre_order (item);
}


void cstree_post_order (CSItem * item)
{
  int ii;
  CSItem * child;
  for (child = item->child; NULL != child; child = child->sibling)
    cstree_post_order (child);
  for (ii = 0; ii < item->depth; ++ii)
    printf ("  ");
  printf ("%c\n", item->data);
}


void cstree_free (CSItem * item)
{
  CSItem * child;
  for (child = item->child; NULL != child; child = child->sibling)
    cstree_free (child);
  free (item);
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
