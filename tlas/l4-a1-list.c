#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct item_s {
  int data;
  struct item_s * next;
} Item;


typedef struct list_s {
  Item * head;
  Item * tail;
} List;


List * list_create (void)
{
  List * list;
  list = calloc (1, sizeof *list);
  return list;
}


void list_destroy (List * list)
{
  Item * tmp;
  while (NULL != list->head) {
    tmp = list->head->next;
    free (list->head);
    list->head = tmp;
  }
  free (list);
}


int list_append (List * list, int data)
{
  Item * item;
  
  item = malloc (sizeof *item);
  if (NULL == item) {
    return -1;
  }
  item->data = data;
  item->next = NULL;
  
  if (NULL == list->head) {
    list->head = item;
    list->tail = item;
  }
  else {
    list->tail->next = item;
    list->tail = item;
  }
  
  return 0;
}


void list_rem_head (List * list)
{
  Item * tmp;
  
  if (NULL != list->head) {
    tmp = list->head;
    list->head = list->head->next;
    free (tmp);
    if (NULL == list->head) {
      list->tail = NULL;
    }
  }
}


int list_test (void)
{
  static int const data[] = { 3, 14, 15, 92 };
  int ii;
  List * list;
  Item * item;
  
  list = list_create ();
  for (ii = 0; ii < sizeof(data)/sizeof(*data); ++ii) {
    if (0 != list_append (list, data[ii])) {
      list_destroy (list);
      return -1;
    }
  }
  
  ii = 0;
  item = list->head;
  while (ii < sizeof(data)/sizeof(*data) && NULL != item) {
    if (data[ii] != item->data) {
      list_destroy (list);
      return -2;
    }
    ++ii;
    item = item->next;
  }
  if (ii != sizeof(data)/sizeof(*data)) {
    list_destroy (list);
    return -3;
  }
  if (NULL != item) {
    list_destroy (list);
    return -4;
  }
  
  list_rem_head (list);
  
  ii = 1;
  item = list->head;
  while (ii < sizeof(data)/sizeof(*data) && NULL != item) {
    if (data[ii] != item->data) {
      list_destroy (list);
      return -5;
    }
    ++ii;
    item = item->next;
  }
  if (ii != sizeof(data)/sizeof(*data)) {
    list_destroy (list);
    return -6;
  }
  if (NULL != item) {
    list_destroy (list);
    return -7;
  }
  
  list_destroy (list);
  
  return 0;
}


int main (int argc, char ** argv)
{
  printf ("%d\n", list_test ());
  return 0;
}
