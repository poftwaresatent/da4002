#include "l5-a1-code.c"
#include <stdio.h>


static void printInOrder (Node * node)
{
  if (NULL != node->foo) {
    printInOrder (node->foo);
  }
  printf ("%ld\n", node->value);
  if (NULL != node->bar) {
    printInOrder (node->bar);
  }
}


static void printDot (Node * root, int depth)
{
  if (0 == depth) {
    printf ("digraph bstree {\n  graph [overlap=scale];\n");
  }
  if (NULL != root->foo) {
    printf ("  %ld -> %ld [len=2];\n", root->value, root->foo->value);
    printDot (root->foo, depth + 1);
  }
  if (NULL != root->bar) {
    printf ("  %ld -> %ld [len=2];\n", root->value, root->bar->value);
    printDot (root->bar, depth + 1);
  }
  if (0 == depth) {
    printf ("}\n");
  }
}


int main (int argc, char ** argv)
{
  static long data[] = { 5, 3, 13, -7, 3, 7, 42, 3, 6, 12, 11 };
  ContainerOne * bstree;
  ContainerTwo * dblist;
  int ii;
  Node * node;
  
  bstree = calloc (1, sizeof *bstree);
  dblist = calloc (1, sizeof *dblist);
  for (ii = 0; ii < sizeof data / sizeof *data; ++ii) {
    container_one_insert (bstree, data[ii]);
    container_two_insert (dblist, data[ii]);
  }
  
  printDot (bstree->handle, 0);
  
  printf ("\n# doubly linked list (forward):\n");
  for (node = dblist->alpha; node != NULL; node = node->foo) {
    printf ("# %ld\n", node->value);
  }
  printf ("\n# doubly linked list (reverse):\n");
  for (node = dblist->beta; node != NULL; node = node->bar) {
    printf ("# %ld\n", node->value);
  }
  
  return 0;
}
