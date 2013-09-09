#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>


/*
  Data structure definition for the stack items. Just the same as
  singly-linked list items (except now we store strings, and before we
  stored integers).
  
  (Do not change this.)
*/
typedef struct item_s {
  char const * string;
  struct item_s * next;
} Item;


/*
  Data structure definition for the stack. Notice that we only need a
  head now, so it would not really be necessary to define a separate
  struct for this.
  
  (Do not change this.)
*/
typedef struct stack_s {
  Item * head;
} Stack;


/*
  FILL IN THIS FUNCTION FOR EXERCISE 4.2
  
  Function to create an empty stack. You can copy-paste adapt the list
  creation function from exercise 4.1.
*/
Stack * create (void)
{
  Stack * stack;
  
  stack = calloc (1, sizeof *stack);
  if (NULL == stack) {
    err (EXIT_FAILURE, "%s: calloc", __func__);
  }
  
  return stack;
}


/*
  FILL IN THIS FUNCTION FOR EXERCISE 4.2
  
  Function to push a string onto our stack.  You can copy-paste adapt
  the appropriate function from exercise 4.1.
*/
void push (Stack * stack, char const * string)
{
  Item * item;
  
  item = malloc (sizeof *item);
  if (NULL == item) {
    err (EXIT_FAILURE, "%s: malloc", __func__);
  }
  item->string = string;
  
  if (NULL == stack->head) {
    item->next = NULL;
    stack->head = item;
  }
  else {
    item->next = stack->head;
    stack->head = item;
  }
}


/*
  FILL IN THIS FUNCTION FOR EXERCISE 4.2
  
  Function to "pop" a string off the stack. This should remove the
  first item from the stack and return the string that was stored
  there. Remember to free the memory that was occupied by the stack
  item.
*/
char const * pop (Stack * stack)
{
  Item * tmp;
  char const * string;
  
  if (NULL == stack->head) {
    return NULL;
  }
  
  tmp = stack->head;
  string = tmp->string;
  stack->head = stack->head->next;
  free (tmp);
  
  return string;
}


/*
  Function to delete all items of a stack as well as the stack itself.
  It gives memory back to the system by calling free().
  
  (Do not change this.)
*/
void destroy (Stack * stack)
{
  Item * tmp;
  while (NULL != stack->head) {
    tmp = stack->head->next;
    free (stack->head);
    stack->head = tmp;
  }
  free (stack);
}


/*
  Main function to test the stack operations.  It pushes all command
  line arguments onto the stack, then pops them off one-by-one,
  printing each on a line by itselfs.
  
  (Do not change this.)
*/
int main (int argc, char ** argv)
{
  int ii;
  Stack * stack;
  char const * string;
  
  stack = create ();
  for (ii = 0; ii < argc; ++ii) {
    push (stack, argv[ii]);
  }
  
  for (string = pop (stack); NULL != string; string = pop (stack)) {
    printf ("%s\n", string);
  }
  
  destroy (stack);
  
  return 0;
}
