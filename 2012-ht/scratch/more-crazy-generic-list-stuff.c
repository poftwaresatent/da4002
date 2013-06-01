#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct item_s {
  void * data;
  struct item_s * next;
} Item;


typedef struct list_s {
  unsigned int size;
  Item * head;
  Item * tail;
  void (*free_data)(void*);
} List;


void list_init (List * list, void (*free_data)(void*))
{
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  list->free_data = free_data;
}


void list_destroy (List * list)
{
  while (NULL != list->head) {
    Item * next = list->head->next;
    if (NULL != list->free_data)
      list->free_data (list->head->data);
    free (list->head);
    list->head = next;
  }
  list->tail = NULL;
  list->size = 0;
  list->free_data = NULL;
}


int list_ins_next (List * list, Item * pos, void * data)
{
  Item * item;
  if (NULL == (item = malloc (sizeof(Item))))
    return -1;
  item->data = data;
  
  if (NULL == pos) {
    /* insert at the head of the list */
    if (0 == list->size)
      list->tail = item;
    item->next = list->head;
    list->head = item;
  }
  else {
    /* insert after the given position */
    if (NULL == pos->next) /* pos is the current tail */
      list->tail = item;
    item->next = pos->next;
    pos->next = item;
  }
  
  ++(list->size);
  return 0;
}


int list_rem_next (List * list, Item * pos)
{
  Item * tmp;
  if (0 == list->size)
    return -1;
  
  if (NULL == pos) {
    /* remove the head */
    if (NULL != list->free_data)
      list->free_data (list->head->data);
    tmp = list->head->next;
    free (list->head);
    list->head = tmp;
    if (NULL == tmp) /* that was the last remaining item */
      list->tail = NULL;
  }
  else {
    /* remove the next element */
    tmp = pos->next;
    if (NULL == tmp)
      return -2;
    pos->next = tmp->next;
    if (NULL != list->free_data)
      list->free_data (tmp->data);
    free (tmp);
    if (NULL == pos->next)
      list->tail = pos;
  }
  
  --(list->size);
  return 0;
}


typedef void (*list_apply_fct_t)(void*);

void list_apply (List * list, void (*fct)(void*))
{
  Item * item;
  for (item = list->head; NULL != item; item = item->next)
    fct (item->data);
}


void int_print (int * number)
{
  printf ("  %d\n", *number);
}


void str_print (char ** string)
{
  printf ("  %s\n", *string);
}


int list_remove_if (List * list,
		    int (*condition)(void*, void*),
		    void * condarg)
{
  Item * it;
  while ((NULL != list->head) && condition (list->head->data, condarg))
    if (0 != list_rem_next (list, NULL))
      return -1;
  for (it = list->head; NULL != it->next; /* nop */)
    if (condition (it->next->data, condarg)) {
      if (0 != list_rem_next (list, it))
	return -2;
    }
    else {
      it = it->next;
    }
  return 0;
}


int int_less_than (int * lhs, int * rhs)
{
  return (*lhs) < (*rhs) ? 1 : 0;
}


int str_starts_with (char ** str, char * letter)
{
  return **str == *letter ? 1 : 0;
}


int main (int argc, char ** argv)
{
  int intarr[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
  int ii;
  char aa;
  List list;
  
  /*
   * Let's store some integers in our generic list. We'll set the
   * free_data function to NULL because we do not want the list to
   * destroy the data for us. In fact, these integers are not
   * allocated on the heap, and thus calling free on them would crash
   * the program.
   */
  
  list_init (&list, NULL);
  for (ii = 0; ii < sizeof(intarr)/sizeof(*intarr); ++ii)
    if (0 != list_ins_next (&list, list.head, intarr + ii)) {
      printf ("failed to insert %d into list of integers\n", intarr[ii]);
      list_destroy (&list);
      return 1;
    }
  printf ("list of integers after initialization:\n");
  list_apply (&list, int_print);
  
  /*
    Let's remove some items based on the generic list_remove_if algorithm.
  */
  
  ii = 10;
  if (0 != list_remove_if (&list, int_less_than, &ii)) {
    printf ("list_remove_if failed on list of integers\n");
    list_destroy (&list);
    return 1;
  }
  printf ("list of integers after removing those that are smaller than 10:\n");
  list_apply (&list, int_print);
  
  /*
    We're done with the list of ints, make sure we give back all
    memory and clear its contents so that we can reuse it for other
    things...
  */
  
  list_destroy (&list);
  
  /*
   * Now, let's store a list of strings, reusing THE SAME generic list
   * instance. Notice that we properly destroy it first, to make sure
   * we do not mix integers with character-arrays. Also notice that
   * now we set the free_data function to the standard free function,
   * because we will place duplicates of our program arguments into
   * the list.
   */

  list_init (&list, free);
  for (ii = 1; ii < argc; ++ii) {
    char * str = strdup (argv[ii]);
    if (NULL == str) {
      printf ("failed to duplicate argument %s\n", argv[ii]);
      list_destroy (&list);
      return 1;
    }
    if (0 != list_ins_next (&list, list.head, str)) {
      printf ("failed to insert %s into list of strings\n", str);
      free (str);
      list_destroy (&list);
      return 1;
    }
  }
  
  printf ("list of strings after initialization:\n");
  list_apply (&list, str_print);
  
  /*
    Let's remove all items that start with the letter 'a'.
  */
  aa = 'a';
  if (0 != list_remove_if (&list, str_starts_with, &aa)) {
    printf ("list_remove_if failed on list of strings\n");
    list_destroy (&list);
    return 1;
  }
  printf ("list of strings after removing those that start with 'a':\n");
  list_apply (&list, str_print);
  
  list_destroy (&list);
  return 0;
}
