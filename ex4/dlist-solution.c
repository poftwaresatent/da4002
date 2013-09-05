#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


typedef struct item_s {
  int data;
  struct item_s * next;
  struct item_s * prev;
} Item;


typedef struct list_s {
  Item * head;
  Item * tail;
} List;


List * create (void)
{
  List * list;
  
  list = calloc (1, sizeof *list);
  if (NULL == list) {
    err (EXIT_FAILURE, "%s: calloc", __func__);
  }
  
  return list;
}


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


void ins_after (List * list, Item * pos, int data)
{
  Item * item;
  
  /* optional */
  if (NULL == pos) {
    prepend (list, data);
    return;
  }
  
  if (pos == list->tail) {
    append (list, data);
    return;
  }
  
  item = malloc (sizeof *item);
  if (NULL == item) {
    err (EXIT_FAILURE, "%s: malloc", __func__);
  }
  item->data = data;
  item->next = pos->next;
  item->prev = pos;
  item->next->prev = item;
  item->prev->next = item;
}


void ins_before (List * list, Item * pos, int data)
{
  Item * item;
  
  /* optional */
  if (NULL == pos) {
    append (list, data);
    return;
  }
  
  if (pos == list->head) {
    prepend (list, data);
    return;
  }
  
  item = malloc (sizeof *item);
  if (NULL == item) {
    err (EXIT_FAILURE, "%s: malloc", __func__);
  }
  item->data = data;
  item->next = pos;
  item->prev = pos->prev;
  item->next->prev = item;
  item->prev->next = item;
}


void rem_item (List * list, Item * item)
{
  if (item == list->head) {
    list->head = item->next;
    if (NULL == list->head) {
      list->tail = NULL;
    }
    else {
      list->head->prev = NULL;
    }
  }
  else if (item == list->tail) {
    list->tail = item->prev;
    list->tail->next = NULL;
  }
  else {
    item->prev->next = item->next;
    item->next->prev = item->prev;
  }
  
  free (item);
}


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


int main (int argc, char ** argv)
{
  static int const data[] = { 3, 14, 15, 92, 65, 359 };
  int ii;
  List * list;
  
  list = create ();
  for (ii = 0; ii < sizeof(data)/sizeof(*data); ++ii) {
    append (list, data[ii]);
  }
  
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("removing head...\n");
  rem_item (list, list->head);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("removing tail...\n");
  rem_item (list, list->tail);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("removing second item...\n");
  rem_item (list, list->head->next);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("inserting after head...\n");
  ins_after (list, list->head, -1);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("inserting after tail...\n");
  ins_after (list, list->tail, -2);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("inserting after 2nd item...\n");
  ins_after (list, list->head->next, -3);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("inserting before head...\n");
  ins_before (list, list->head, -11);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("inserting before tail...\n");
  ins_before (list, list->tail, -22);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  printf ("inserting before 2nd item...\n");
  ins_before (list, list->head->next, -33);
  printf ("forward:");
  print_fwd (list);
  printf ("reverse:");
  print_rev (list);
  
  destroy (list);
  
  return 0;
}
