#include <err.h>
#include <stdlib.h>
#include <stdio.h>


static int *array;
static size_t length;


void insert (int value)
{
  size_t index, parent;
  ++length;
  array = realloc (array, (length+1) * sizeof *array);
  index = length;
  array[index] = value;
  parent = index / 2;
  while ((parent > 0) && (array[index] < array[parent])) {
    array[0] = array[index];
    array[index] = array[parent];
    array[parent] = array[0];
    index = parent;
    parent = index / 2;
  }
}


void bubble_down (void)
{
  size_t parent, target, child;
  parent = 1;
  target = 1;
  while (1) {
    child = 2 * parent;
    if (child <= length && array[child] < array[target])
      target = child;
    ++child;
    if (child <= length && array[child] < array[target])
      target = child;
    if (parent == target)
      break;
    array[0] = array[target];
    array[target] = array[parent];
    array[parent] = array[0];
    parent = target;
  }
}


void bubble_down_buggy (void)
{
  size_t parent, target, child;
  parent = 0;
  target = 0;
  while (1) {
    child = 2 * parent;
    if (child <= length && array[child] < array[target])
      target = child;
    ++child;
    if (child <= length && array[child] < array[target])
      target = child;
    if (parent == target)
      break;
    array[0] = array[target];
    array[target] = array[parent];
    array[parent] = array[0];
    parent = target;
  }
}


int dequeue (void)
{
  int it;
  if (0 == length) {
    errx (EXIT_FAILURE,  __FILE__": %s: empty heap", __func__);
  }
  it = array[1];
  if (1 == length) {
    free (array);
    array = NULL;
    length = 0;
    return it;
  }
  array[1] = array[length];
  array = realloc (array, length * sizeof *array);
  if (NULL == array)
    errx (EXIT_FAILURE, __FILE__": %s: realloc", __func__);
  --length;
  bubble_down_buggy ();
  return it;
}


void dump (void)
{
  if (0 == length) {
    printf ("  EMPTY\n");
  }
  else {
    size_t ii;
    for (ii = 1; ii <= length; ++ii)
      printf ("  %d", array[ii]);
    printf ("\n");
  }
}


int main (int argc, char **argv)
{
  int ii;
  
  if (2 > argc) {
    fprintf (stderr,
	     "Please provide a sequence of integer values to put onto the heap.\n"
	     "For example, give the following command:\n"
	     "  %s 1 2 3 1 2 5 4 3\n",
	     argv[0]);
    return 42;
  }
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, "argument %d `%s' is not an integer", ii, argv[ii]);
    insert (num);
    fprintf (stdout, "inserted %d\n", num);
    dump ();
  }
  
  printf ("repeated removal (to see the buggy behavior for Q6)\n");
  while (length > 0) {
    printf ("  %d\n", dequeue ());
  }
  return 0;
}
