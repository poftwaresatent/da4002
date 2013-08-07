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


typedef struct queue_item_s {
  CSItem *node;
  struct queue_item_s *next;
} QueueItem;


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


QueueItem * queue_item_new (CSItem * node)
{
  QueueItem * item;
  item = calloc (1, sizeof *item);
  if (NULL == item)
    err (EXIT_FAILURE, "queue_item_new: calloc");
  item->node = node;
  return item;
}


QueueItem * queue_item_next (QueueItem * head)
{
  QueueItem * next;
  next = head->next;
  free (head);
  return next;
}


void cstree_level_order (CSItem * root)
{
  int ii;
  CSItem * child;
  QueueItem *head, *tail;
  head = queue_item_new (root);
  tail = head;
  while (NULL != head) {
    for (ii = 0; ii < head->node->depth; ++ii) {
      printf ("  ");
    }
    printf ("%c\n", head->node->data);
    for (child = head->node->child; NULL != child; child = child->sibling) {
      tail->next = queue_item_new (child);
      tail = tail->next;
    }
    head = queue_item_next (head);
  }
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
  const char * spec = "A(D(G(IH))B(FEC))";
  
  printf ("initializing tree\n");
  root = cstree_parse (NULL, &spec);
  
  printf ("computing depth\n");
  cstree_compute_depth (root, -1);
  
  printf ("post-order traversal:\n");
  cstree_post_order (root);
  
  printf ("pre-order traversal:\n");
  cstree_pre_order (root);
  
  printf ("level-order traversal:\n");
  cstree_level_order (root);
  
  cstree_free (root);
  return 0;
}
