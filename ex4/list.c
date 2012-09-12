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


int list_rem (List * list, Item * pos)
{
  printf ("Please implement list_rem.\n");
  return -1;
}


void person_print (Person * person)
{
  printf ("  %-15s is %2u year%-1s old\n",
	  person->name,
	  person->age,
	  person->age > 1 ? "s" : "");
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


int main (int argc, char ** argv)
{
  List list;
  Item * it;
  
  list_init (&list);
  
  if (0 != populate (&list)) {
    list_destroy (&list);
    return 1;
  }
  
  printf ("population:\n");
  list_dump (&list);
  
  for (it = list.head; it != NULL; it = it->next)
    if ((18 > it->data->age)
	&& (0 != list_rem (&list, it))) {
      printf ("failed to remove %s\n", it->data->name);
      list_destroy (&list);
      return 1;
    }
  
  printf ("\npersons allowed to vote:\n");
  list_dump (&list);
  
  list_destroy (&list);
  return 0;
}
