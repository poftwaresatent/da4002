#include <stdlib.h>


typedef struct node_s {
  long value;
  struct node_s * foo;
  struct node_s * bar;
} Node;


typedef struct {
  Node * handle;
} ContainerOne;


typedef struct {
  Node * alpha;
  Node * beta;
} ContainerTwo;


static Node * helper (long value, Node * node)
{
  if (NULL == node) {
    node = malloc (sizeof *node);
    node->value = value;
    node->foo = NULL;
    node->bar = NULL;
    return node;
  }
  
  if (value < node->value) {
    node->foo = helper(value, node->foo);
  }
  else if (value > node->value) {
    node->bar = helper(value, node->bar);
  }
  
  return node;
}


void container_one_insert (ContainerOne * container, long value)
{
  container->handle = helper (value, container->handle);
}


void container_two_insert (ContainerTwo * container, long value)
{
  Node * node = malloc (sizeof *node);
  node->value = value;
  node->foo = NULL;
  node->bar = NULL;
  
  if (NULL == container->beta) {
    container->alpha = node;
    container->beta = node;
    return;
  }
  
  container->beta->foo = node;
  node->bar = container->beta;
  container->beta = node;
}
