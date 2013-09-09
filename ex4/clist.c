#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


/*
  As usual, a list item contains some data and a pointer to the next
  item.

  (Do not change this struct.)
*/
typedef struct item_s {
  int data;
  struct item_s * next;
} Item;


/*
  As usual, the list itsels contains a pointer to the head and a
  pointer to the tail.

  (Do not change this struct.)
*/
typedef struct list_s {
  Item * head;
  Item * tail;
} List;


/*
  No surprise here, either.
  
  (Do not change this function.)
*/
List * create (void)
{
  List * list;
  
  list = calloc (1, sizeof *list);
  if (NULL == list) {
    err (EXIT_FAILURE, "%s: calloc", __func__);
  }
  
  return list;
}


/*
  FILL IN THIS FUNCTION FOR EXERCISE 4.3
  
  Appending to a circular list is almost the same as for a normal
  list, except that the tail needs to point to the head.
*/
void append (List * list, int data)
{
}


/*
  FILL IN THIS FUNCTION FOR EXERCISE 4.3
  
  Prepending to a circular list, again, is almost the same as for a
  normal list... except that the tail needs to point to the head.
*/
void prepend (List * list, int data)
{
}


/*
  For illustration purposes, this print function receives an extra
  argument with the number of items that should be printed. The idea
  is to show that following the "next" pointers will lead us around in
  circles.
  
  (Do not change this function.)
*/
void print (List * list, int count)
{
  Item * item;
  if (NULL == list->head) {
    printf ("  [empty]\n");
  }
  else {
    printf (" ");
    for (item = list->head; count > 0; --count) {
      printf (" %3d", item->data);
      item = item->next;
    }
    printf ("\n");
  }
}


/*
  Freeing up the memory of a circular list is basically the same as
  for all other lists, but here we need to be careful: blindly
  following the "next" pointers would lead us back to the head, which
  got freed in the meantime, which would be an error.
  
  (Do not change this function.)
*/
void destroy (List * list)
{
  Item * tmp;
  if (NULL != list->tail) {
    list->tail->next = NULL;
  }
  while (NULL != list->head) {
    tmp = list->head->next;
    free (list->head);
    list->head = tmp;
  }
  free (list);
}


/*
  Here we append and prepend some data items to a circular list, and
  then simply print varying numbers of items to illustrate that the
  list "wraps around."
  
  (Do not change this function.)
*/
int main (int argc, char ** argv)
{
  static int const data[] = { 1, 2, 3, 4, 5, 6 };
  int ii;
  List * list;
  
  list = create ();
  for (ii = 0; ii < sizeof(data)/sizeof(*data); ++ii) {
    if (0 == ii % 2) {
      append (list, data[ii]);
    }
    else {
      prepend (list, data[ii]);
    }
  }
  
  for (ii = 6; ii <= 15; ii += 3) {
    printf ("%2d elements:", ii);
    print (list, ii);
  }
  
  destroy (list);
  
  return 0;
}
