#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <err.h>


typedef struct node_s {
  char data;
  int depth;
  struct node_s * cld;
  struct node_s * sbl;
} Node;


typedef struct fifo_item_s {
  Node * node;
  struct fifo_item_s * next;
} FifoItem;


typedef struct fifo_s {
  FifoItem * head, * tail;
} Fifo;


Fifo * fifo_create ()
{
  Fifo * fifo;
  fifo = calloc (1, sizeof *fifo);
  if (NULL == fifo) {
    err (EXIT_FAILURE, "fifo_create: calloc");
  }
  return fifo;
}


void fifo_append (Fifo * fifo, Node * node)
{
  FifoItem * item;
  item = calloc (1, sizeof *item);
  if (NULL == item) {
    err (EXIT_FAILURE, "fifo_append: calloc");
  }
  item->node = node;
  if (NULL == fifo->head) {
    fifo->head = item;
    fifo->tail = item;
  }
  else {
    fifo->tail->next = item;
    fifo->tail = fifo->tail->next;
  }
}


Node * fifo_extract (Fifo * fifo)
{
  Node * node;
  FifoItem * tmp;
  if (NULL == fifo->head) {
    return NULL;
  }
  node = fifo->head->node;
  tmp = fifo->head->next;
  free (fifo->head);
  fifo->head = tmp;
  return node;
}


void fifo_destroy (Fifo * fifo)
{
  while (NULL != fifo->head) {
    FifoItem * tmp;
    tmp = fifo->head->next;
    free (fifo->head);
    fifo->head = tmp;
  }
  free (fifo);
}


Node * node_new (char data)
{
  Node * it = calloc (1, sizeof (*it));
  if (NULL == it) {
    err (EXIT_FAILURE, "node_new: calloc");
  }
  it->data = data;
  return it;
}


Node * cstree_parse (Node * parent, const char ** spec)
{
  Node *child = NULL;
  
  while ('\0' != **spec){
    
    if (isspace (**spec)) {
      ++(*spec);
      continue;
    }
    
    if (')' == **spec) {
      if (NULL == child) {
	errx (EXIT_FAILURE, "cstree_parse: empty sibling list");
      }
      ++(*spec);
      return child;
    }
    
    if (isalnum (**spec)) {
      Node *next;
      if (NULL == parent && NULL != child) {
	errx (EXIT_FAILURE, "cstree_parse: the root cannot have siblings");
      }
      next = node_new (**spec);
      next->sbl = child;
      child = next;
      if (NULL != parent) {
	parent->cld = child;
      }
      ++(*spec);
      continue;
    }
    
    if ('(' == **spec) {
      if (NULL == child) {
	errx (EXIT_FAILURE, "cstree_parse: sibling list without parent");
      }
      ++(*spec);
      cstree_parse (child, spec);
      continue;
    }
    
    errx (EXIT_FAILURE, "cstree_parse: invalid character `%c'", **spec);
  }
  
  if (NULL == child) {
    errx (EXIT_FAILURE, "cstree_parse: empty root sibling list or unbalanced parenthesis");
  }
  
  return child;
}


void cstree_compute_depth (Node * node, int parent_depth)
{
  node->depth = ++parent_depth;
  for (node = node->cld; NULL != node; node = node->sbl) {
    cstree_compute_depth (node, parent_depth);
  }
}


void cstree_pre_order (Node * node)
{
  int ii;
  for (ii = 0; ii < node->depth; ++ii) {
    printf ("  ");
  }
  printf ("%c\n", node->data);
  for (node = node->cld; NULL != node; node = node->sbl)
    cstree_pre_order (node);
}


void cstree_post_order (Node * node)
{
  int ii;
  Node * child;
  for (child = node->cld; NULL != child; child = child->sbl)
    cstree_post_order (child);
  for (ii = 0; ii < node->depth; ++ii)
    printf ("  ");
  printf ("%c\n", node->data);
}


void cstree_level_order (Node * node)
{
  int ii;
  Fifo * fifo;
  fifo = fifo_create ();
  while (NULL != node) {
    for (ii = 0; ii < node->depth; ++ii) {
      printf ("  ");
    }
    printf ("%c\n", node->data);
    for (node = node->cld; NULL != node; node = node->sbl) {
      fifo_append (fifo, node);
    }
    node = fifo_extract (fifo);
  }
  fifo_destroy (fifo);
}


void cstree_free (Node * node)
{
  Node * child;
  for (child = node->cld; NULL != child; child = child->sbl)
    cstree_free (child);
  free (node);
}


int main (int argc, char ** argv)
{
  Node * root;
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
