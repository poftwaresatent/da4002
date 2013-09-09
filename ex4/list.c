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
  item->next = NULL;
  
  if (NULL == list->head) {
    list->head = item;
    list->tail = item;
  }
  else {
    list->tail->next = item;	/* what happens if you swap these two lines? */
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
  
  if (NULL == list->head) {
    item->next = NULL;
    list->head = item;
    list->tail = item;
  }
  else {
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
  pos->next = item;
}


void rem_head (List * list)
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


void print (List * list)
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
  List * fwd;
  List * rev;
  
  fwd = create ();
  rev = create ();
  for (ii = 0; ii < sizeof(data)/sizeof(*data); ++ii) {
    append (fwd, data[ii]);
    prepend (rev, data[ii]);
  }
  
  printf ("forward:");
  print (fwd);
  printf ("reverse:");
  print (rev);
  
  ins_after (fwd, fwd->head, -11);
  printf ("ins_after head:    ");
  print (fwd);
  
  ins_after (fwd, fwd->tail, -22);
  printf ("ins_after tail:    ");
  print (fwd);
  
  ins_after (fwd, fwd->head->next, -33);
  printf ("ins_after 2nd item:");
  print (fwd);
  
  while (NULL != fwd->head) {
    rem_head (fwd);
    printf ("removed head:");
    print (fwd);
  }
  
  destroy (fwd);
  destroy (rev);
  
  return 0;
}
