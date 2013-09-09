#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


/*
  List items for doubly-linked lists need a pointer to the previous
  item as well as to the next item.
  
  (Do not change this.)
*/
typedef struct item_s {
  int data;
  struct item_s * next;
  struct item_s * prev;
} Item;


/*
  The list structure itself still just needs a head and a tail.
  
  (Do not change this.)
*/
typedef struct list_s {
  Item * head;
  Item * tail;
} List;


/*
  The usual list creation function.
  
  (Do not change this.)
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
  Appending to a doubly-linked list is slightly more involved than for
  a singly linked list, because the "prev" pointers need to get
  updated. But there is no big surprise here.
  
  (Do not change this.)
*/
void append (List * list, int data)
{
  Item * item;
  
  item = malloc (sizeof *item);
  if (NULL == item) {
    err (EXIT_FAILURE, "%s: malloc", __func__);
  }
  item->data = data;
  item->next = NULL;
  
  if (NULL == list->head) {
    list->head = item;
    list->tail = item;
    item->prev = NULL;
  }
  else {
    list->tail->next = item;
    item->prev = list->tail;
    list->tail = item;
  }
}


/*
  Prepending is also not much different from the singly-linked case.
  
  (Do not change this.)
*/
void prepend (List * list, int data)
{
  Item * item;
  
  item = malloc (sizeof *item);
  if (NULL == item) {
    err (EXIT_FAILURE, "%s: malloc", __func__);
  }
  item->data = data;
  item->prev = NULL;
  
  if (NULL == list->head) {
    item->next = NULL;
    list->head = item;
    list->tail = item;
  }
  else {
    list->head->prev = item;
    item->next = list->head;
    list->head = item;
  }
}


/*
  IMPLEMENT THIS for exercise 4.4.1
  
  One of the important features of doubly-linked lists is that
  removing an element is quite easy, because it is always possible to
  find the predecessor and the successor of a given item. Draw a
  diagram of the required operations and implement them here. Do not
  forget to update the "prev" pointers!
  
  Be careful with the special cases: the given item could be the head
  or the tail of the list! Also, it could be the only element he list,
  which ans thatafter movg the item the list should empty.
  
  Also be sure to free() the memory that was occupied by the element
  that is being removed!
*/
void rem_item (List * list, Item * item)
{
}


/*
  IMPLEMENT THIS for exercise 4.4.2
  
  Inserting elements after a given position is very similar to the
  case of the singly-linked list (see exercise 4.1), but of course the
  "prev" pointer needs to be correctly handled. And be sure to
  properly update the tail and/or head of the list as appropriate!
  
  A nice optional feature for this kind of function is to be able to
  pass a NULL position, in which case the function should be the same
  as prepend().
*/
void ins_after (List * list, Item * pos, int data)
{
}


/*
  IMPLEMENT THIS for exercise 4.4.3
  
  Inserting elements /before/ a given position is something that is
  much easier to do with doubly-linked than with singly-linked
  lists. This is very similar to ins_after().
  
  Again, a nice optional feature is to be able to pass a NULL
  position. In this case, as opposed to ins_after(), we would like the
  function to append() when NULL is given as position.
*/
void ins_before (List * list, Item * pos, int data)
{
}


/*
  Another useful feature of doubly-linked lists is that one can easily
  iterate forward or in reverse. This function just prints the list
  contents from head to tail...
  
  (Do not change this.)
*/
void print_fwd (List * list)
{
  Item * item;
  if (NULL == list->head) {
    printf ("  [empty]\n");
  }
  else {
    printf (" ");
    for (item = list->head; NULL != item; item = item->next) {
      printf (" %3d", item->data);
    }
    printf ("\n");
  }
}


/*
  ...whereas this function prints the list from tail to head (in reverse).
  
  (Do not change this.)
*/
void print_rev (List * list)
{
  Item * item;
  if (NULL == list->head) {
    printf ("  [empty]\n");
  }
  else {
    printf (" ");
    for (item = list->tail; NULL != item; item = item->prev) {
      printf (" %3d", item->data);
    }
    printf ("\n");
  }
}


/*
  Freeing up the memory used by a list is the same for doubly-linked
  lists as for singly-linked lists.
  
  (Do not change this.)
*/
void destroy (List * list)
{
  Item * tmp;
  while (NULL != list->head) {
    tmp = list->head->next;
    free (list->head);
    list->head = tmp;
  }
  free (list);
}


/*
  This program tests the doubly-linked list functions above by
  creating and modifying a list.
*/
int main (int argc, char ** argv)
{
  static int const data[] = { 3, 14, 15, 92, 65, 359 };
  int ii;
  List * list;
  
  list = create ();
  for (ii = 0; ii < sizeof(data)/sizeof(*data); ++ii) {
    append (list, data[ii]);
  }
  
  printf ("initial list...\n");
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("removing head...\n");
  rem_item (list, list->head);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("removing tail...\n");
  rem_item (list, list->tail);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("removing second item...\n");
  rem_item (list, list->head->next);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("inserting after head...\n");
  ins_after (list, list->head, -1);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("inserting after tail...\n");
  ins_after (list, list->tail, -2);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("inserting after 2nd item...\n");
  ins_after (list, list->head->next, -3);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("inserting before head...\n");
  ins_before (list, list->head, -11);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("inserting before tail...\n");
  ins_before (list, list->tail, -22);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  printf ("inserting before 2nd item...\n");
  ins_before (list, list->head->next, -33);
  printf ("  forward:");
  print_fwd (list);
  printf ("  reverse:");
  print_rev (list);
  
  destroy (list);
  
  return 0;
}
