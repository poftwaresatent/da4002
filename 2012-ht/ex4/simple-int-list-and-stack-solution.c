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


void list_init (List * list)
{
  memset (list, 0, sizeof (*list));
}


void list_ins_next (List * list, Item * pos, int data)
{
  Item * item;
  if (NULL == (item = malloc (sizeof (*item))))
    err (EXIT_FAILURE, "list_ins_next: malloc");
  item->data = data;
  
  if (NULL == pos) {
    /* insert at the head of the list */
    if (NULL == list->head)	/* empty list */
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
}


int list_rem_next (List * list, Item * pos)
{
  int result;
  
  if (NULL == list->head)
    errx (EXIT_FAILURE, "list_rem_next: empty list");
  
  if (NULL == pos) {
    /* remove the head */
    result = list->head->data;
    list->head = list->head->next;
    if (NULL == list->head) /* that was the last remaining item */
      list->tail = NULL;
  }
  else {
    /* remove the next element */
    if (NULL == pos->next)
      errx (EXIT_FAILURE, "list_rem_next: no next element");
    result = pos->data;
    pos->next = pos->next->next;
    if (NULL == pos->next)	/* we removed the old tail... */
      list->tail = pos;
  }
  
  return result;
}


void list_dump (List * list)
{
  Item * item;
  printf (" ");
  if (NULL == list->head)
    printf (" [empty]\n");
  else  
    for (item = list->head; NULL != item; item = item->next)
      printf (" %3d", item->data);
}


void populate (List * list)
{
  static int const age[] = { 28, 31, 1, 5, 42, 43, 19, 17, 15 };
  int ii;
  
  for (ii = 0; ii < sizeof(age)/sizeof(*age); ++ii)
    list_ins_next (list, list->tail, age[ii]);
}


void test_list (void)
{
  List list;
  Item * it;
  
  printf ("==================================================\n"
	  "singly-linked list\n"
	  "--------------------------------------------------\n");
  
  list_init (&list);
  populate (&list);
  
  printf ("list after init:\n");
  list_dump (&list);
  printf ("\n\n");
  
  while ((NULL != list.head) && (18 > list.head->data )) {
    printf ("removing %d from head\n", list.head->data);
    list_rem_next (&list, NULL);
  }
  for (it = list.head; NULL != it->next; /* nop */) {
    if (18 > it->next->data) {
      printf ("removing %d\n", it->next->data);
      list_rem_next (&list, it);
    }
    else
      it = it->next;
  }
  
  printf ("\nafter removing numbers smaller than 18:\n");
  list_dump (&list);
  printf ("\n");
}


typedef List Stack;


void stack_push (Stack * stack, int data)
{
  list_ins_next (stack, NULL, data);
}


int stack_pop (Stack * stack)
{
  return list_rem_next (stack, NULL);
}


void test_stack (void)
{
  static const int input[] = { 1, 2, 3, 4, 5 };
  int ii;
  Stack stack;
  
  printf ("==================================================\n"
	  "stack (based on singly-linked list)\n"
	  "--------------------------------------------------\n");
  
  list_init (&stack);
  for (ii = 0; ii < sizeof(input)/sizeof(*input); ++ii) {
    stack_push (&stack, input[ii]);
    printf ("pushed %d\n", input[ii]);
  }
  
  printf ("\nnow calling pop...\n");
  while (NULL != stack.head)
    printf ("popped %d\n", stack_pop (&stack));
  printf ("\n");
}


int main (int argc, char ** argv)
{
  /*
   * Un-comment test_list after implementing list_rem_next.
   *
   */
  
  test_list ();
  
  /*
   * Un-comment test_stack after implementing stack_push and stack_pop.
   *
   */
  
  test_stack ();
  
  return 0;
}
