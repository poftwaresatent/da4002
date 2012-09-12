#include <stdio.h>
#include <stdlib.h>


typedef struct item_s {
  int value;
  struct item_s * next;
} Item;


typedef struct list_s {
  Item * head;
  Item * tail;
} List;


void list_init (List * list)
{
  list->head = NULL;
  list->tail = NULL;
}


void list_destroy (List * list)
{
  while (NULL != list->head) {
    Item * next = list->head->next;
    free (list->head);
    list->head = next;
  }
  list->tail = NULL;
}


int list_append (List * list, int value)
{
  Item * item;
  item = malloc (sizeof(Item));
  if (NULL == item)
    return -1;
  
  item->value = value;
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


void list_dump (List * list)
{
  Item * item;
  
  if (NULL == list->head) {
    printf ("[empty]\n");
    return;
  }
  
  for (item = list->head; NULL != item; item = item->next)
    printf (" %2d", item->value);
  printf ("\n");
}


int main (int argc, char ** argv)
{
  List list;
  int ii;
  
  list_init (&list);
  printf ("initialized: ");
  list_dump (&list);
  
  for (ii = -3; ii < 17; ++ii) {
    if (0 != list_append (&list, ii)) {
      printf ("ERROR: could not append %d\n", ii);
      return -1;
    }
    printf ("appended %2d: ", ii);
    list_dump (&list);
  }
  
  return 0;
}
