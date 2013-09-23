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
