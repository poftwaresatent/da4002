#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  char * name;
  unsigned int age;
} Person;


typedef struct item_s {
  Person * data;
  struct item_s * next;
} Item;


typedef struct list_s {
  unsigned int size;
  Item * head;
  Item * tail;
} List;


Person * person_create (char const * name, int age)
{
  Person * person;
  if (NULL == (person = malloc (sizeof(*person))))
    return NULL;
  person->name = strdup (name);
  person->age = age;
  return person;
}


void person_destroy (Person * person)
{
  free (person->name);
  free (person);
}


void person_print (Person * person)
{
  printf ("  %-15s is %2u year%-1s old\n",
	  person->name,
	  person->age,
	  person->age > 1 ? "s" : "");
}


void list_init (List * list)
{
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
}


void list_destroy (List * list)
{
  while (NULL != list->head) {
    Item * next = list->head->next;
    person_destroy (list->head->data);
    free (list->head);
    list->head = next;
  }
  list->tail = NULL;
  list->size = 0;
}


int list_ins_next (List * list, Item * pos, Person * data)
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


int list_rem_next (List * list, Item * pos, Person ** data)
{
  Item * tmp;
  if (0 == list->size)
    return -1;
  
  if (NULL == pos) {
    /* remove the head */
    if (NULL == data)
      person_destroy (list->head->data);
    else
      *data = list->head->data;
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
    if (NULL == data)
      person_destroy (tmp->data);
    else
      *data = tmp->data;
    free (tmp);
    if (NULL == pos->next)
      list->tail = pos;
  }
  
  --(list->size);
  return 0;
}


void list_dump (List * list)
{
  Item * item;
  
  if (NULL == list->head) {
    printf ("  [empty]\n");
    return;
  }
  
  for (item = list->head; NULL != item; item = item->next)
    person_print (item->data);
}


int populate (List * list)
{
  static Person const population[] = {
    { "Alice Doe",   28 },
    { "Bob Doe",     31 },
    { "Charlie Doe",  1 },
    { "Doris Doe",    5 },
    { "Arnold Fox",  42 },
    { "Barbara Fox", 43 },
    { "Cindy Fox",   19 },
    { "Daniel Fox",  17 },
    { "Eric Fox",    15 },
    { NULL,           0 }};
  Person const * ip;
  
  for (ip = population; NULL != ip->name; ++ip) {
    Person * pp = person_create (ip->name, ip->age);
    if (NULL == pp) {
      printf ("failed to create %s\n", ip->name);
      return -1;
    }
    if (0 != list_ins_next (list, list->tail, pp)) {
      printf ("failed to insert %s\n", ip->name);
      return -2;
    }
  }
  
  return 0;
}


int stack_push (List * list, Person * person)
{
  return list_ins_next (list, NULL, person);
}


Person * stack_pop (List * list)
{
  Person * person;
  if (0 != list_rem_next (list, NULL, &person))
    return NULL;
  return person;
}


int main (int argc, char ** argv)
{
  List stack;
  Person *person;
  
  /*
    Quick'n'dirty code without error checking, please don't get in the
    habit of doing this...
  */
  list_init (&stack);
  stack_push (&stack, person_create ("Richard Feynman", 2012 - 1918));
  stack_push (&stack, person_create ("Richard The Third", 2012 - 1452));
  stack_push (&stack, person_create ("Richard The First", 2012 - 1157));
  
  while (NULL != (person = stack_pop (&stack)))
    person_print (person);
  
  list_destroy (&stack);
  return 0;
}
