#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


typedef struct item_s {
  int data;
  struct item_s * next;
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
  
  if (NULL == list->head) {
    list->head = item;
    list->tail = item;
    item->next = item;
  }
  else {
    list->tail->next = item;	/* what happens if you swap these two lines? */
    list->tail = item;
    item->next = list->head;
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
  
  if (NULL == list->head) {
    list->head = item;
    list->tail = item;
    item->next = item;
  }
  else {
    item->next = list->head;
    list->head = item;
    list->tail->next = item;
  }
}


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
