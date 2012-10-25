#include <err.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct item_s {
  int value;
  struct item_s *next;
  struct item_s *prev;
} Item;

static Item *head;


void insert (int value)
{
  Item *it = malloc (sizeof *it);
  it->value = value;
  if (NULL == head) {
    it->next = it;
    it->prev = it;
  }
  else {
    it->next = head;
    it->prev = head->prev;
    it->prev->next = it;
    it->next->prev = it;
  }
  head = it;
}


void dump (void)
{
  if (NULL == head)
    printf ("  EMPTY\n");
  else {
    Item *it = head;
    do {
      printf ("  %d", it->value);
      it = it->next;
    } while (head != it);
    printf ("\n");
  }
}


int main (int argc, char **argv)
{
  int ii;
  
  if (2 > argc) {
    fprintf (stderr,
	     "Please provide a sequence of integer values to put onto the heap.\n"
	     "For example, give the following command:\n"
	     "  %s 1 2 3 1 2 5 4 3\n",
	     argv[0]);
    return 42;
  }
  
  for (ii = 1; ii < argc; ++ii) {
    int num;
    if (1 != sscanf (argv[ii], "%d", &num))
      errx (EXIT_FAILURE, "argument %d `%s' is not an integer", ii, argv[ii]);
    insert (num);
    fprintf (stdout, "inserted %d\n", num);
    dump ();
  }
  
  return 0;
}
