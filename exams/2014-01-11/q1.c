#include <stdlib.h>


#define MAXPRIORITY 10


typedef struct item_s {
  int data;
  struct item_s * next;
} Item;


typedef struct {
  Item * head, * tail;
} List;


typedef struct {
  int * data;
  int len, capa;
} Vector;


void function_A (Vector * vec,
                 int data)
{
  if (vec->len == vec->capa) {
    if (vec->capa == 0) {
      vec->capa = 1024;
    }
    else {
      vec->capa *= 2;
    }
    vec->data = realloc (vec->data,
                         vec->capa);
  }
  vec->data[vec->len++] = data;
}


int function_B (Vector * vec)
{
  return vec->data[--vec->len];
}


void function_C (List * list,
                 int data)
{
  Item * item = malloc (sizeof (Item));
  item->data = data;
  item->next = list->head;
  if (list->head == NULL) {
    list->tail = item;
  }
  list->head = item;
}




int function_D (List ** list)
{
  int ii;
  int data;
  Item * tmp;
  for (ii = MAXPRIORITY; ii > 0; --ii) {
    if (list[ii]->head != NULL) {
      break;
    }
  }
  tmp = list[ii]->head;
  data = tmp->data;
  list[ii]->head = tmp->next;
  free (tmp);
  if (list[ii]->head == NULL) {
    list[ii]->tail = NULL;
  }
  return data;
}


int function_E (List * list)
{
  int data = list->head->data;
  Item * tmp = list->head;
  list->head = list->head->next;
  free (tmp);
  if (list->head == NULL) {
    list->tail = NULL;
  }
  return data;
}


void function_F (List ** list,
                 int priority,
                 int data)
{
  Item * item = malloc (sizeof (Item));
  item->data = data;
  item->next = NULL;
  if (list[priority]->head == NULL) {
    list[priority]->head = item;
  }
  list[priority]->tail = item;
}
