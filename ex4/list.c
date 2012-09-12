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


int list_rem_next (List * list, Item * pos, Person ** data)
{
  printf ("Please implement list_rem_next.\n");
  *data = NULL;
  return -1;
}


void person_print (Person * person)
{
  printf ("%s is %u year%s old\n",
	  person->name,
	  person->age,
	  person->age > 1 ? "s" : "");
}


void list_dump (List * list)
{
  Item * item;
  
  if (NULL == list->head) {
    printf ("[empty]\n");
    return;
  }
  
  for (item = list->head; NULL != item; item = item->next)
    person_print (item->data);
}


int main (int argc, char ** argv)
{
  Person inittab[] = {
    { "Alice Doe",   28 },
    { "Bob Doe",     31 },
    { "Charlie Doe",  1 },
    { NULL,           0 }};
  
  List list;
  Person * ip;
  char * msg;
  
  list_init (&list);
  printf ("initialized: ");
  list_dump (&list);
  
  msg = NULL;
  for (ip = inittab; NULL != ip->name; ++ip) {
    Person * pp = person_create (ip->name, ip->age);
    if (NULL == pp) {
      msg = "failed to create person";
      break;
    }
    if (0 != list_ins_next (&list, list.tail, pp)) {
      msg = "failed to insert next item";
      break;
    }
  }
  
  if (NULL != msg) {
    printf ("ERROR: %s\n", msg);
    list_destroy (&list);
    return 1;
  }
  
  list_dump (&list);
  
  list_destroy (&list);
  return 0;
}
