#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE        1024


/*
 * Struct to hold the information needed to store our stack of
 * strings. Here we simply use a vector (dynamic array), although a
 * simply linked list would work as well (see next exercise). Notice
 * the "char **" which is essentially the same kind of thing used to
 * pass the command-line arguments into the main function, namely an
 * array of pointers to characters.
 */
typedef struct stack_s {
  char ** arr;
  unsigned long len;
  unsigned long cap;
} Stack;


/*
 * User function to initialize a stack, essentially the same as
 * vector_init in the previous exercise.
 */
void stack_init (Stack * stack)
{
  stack->arr = NULL;
  stack->len = 0;
  stack->cap = 0;
}


/*
 * User function to destroy a stack. Almost the same as vector_destroy
 * in the previous exercise, except that here WE FREE MEMORY allocated
 * by the strings stored in the stack.
 *
 * \note The fact that all remaining strings are passed to free means
 * that strings stored in this stack should not be shared with other
 * parts of the program, because it may happen that the stack gets
 * destroyed (thus freeing all those strings) while other parts might
 * still want to use them later. This is referred to as the issue of
 * ownership, and it can frequently cause problems in languages such
 * as C or C++ which require the programmer to do their own memory
 * management.
 */
void stack_destroy (Stack * stack)
{
  char *str;

  if (NULL == stack->arr)
    return;

  for (str = *stack->arr; 0 < stack->len; --stack->len, ++str)
    free (str);
  free (stack->arr);
  stack->arr = NULL;
  stack->cap = 0;
}


/* **************************************************
 * * FILL IN THIS FUNCTION **************************
 * **************************************************
 *
 * Utility function used internally by the stack when more memory is
 * required.
 *
 * \return zero on success.
 */
int stack_grow (Stack * stack)
{
  /*
    HINT: This is essentially the same as vector_grow() from the
    previous exercise.
  */
  printf ("Please implement stack_grow!\n");
  return -100;
}


/* **************************************************
 * * FILL IN THIS FUNCTION **************************
 * **************************************************
 *
 * User function to place a string onto the top of the stack.
 *
 * \note This function does not make a separate copy of the string,
 * assuming that the user will manage their memory separately.  But if
 * stack_destroy is called while the stack still contains this string,
 * then free will be called on it.
 *
 * \return zero on success.
 */
int stack_push (Stack * stack, char * str)
{
  /*
    HINT: This is essentially the same as vector_append() from the
    previous exercise.
  */
  printf ("Please implement stack_grow!\n");
  return -100;
}


/* **************************************************
 * * FILL IN THIS FUNCTION **************************
 * **************************************************
 *
 * User function to retrieve the string which is currently on top of
 * the stack.
 *
 * \note It is up to the user to free the returned string at the
 * appropriate moment.
 *
 * \return The topmost string, or NULL if the stack is empty.
 */
char * stack_pop (Stack * stack)
{
  /*
    HINT: This is essentially the same as vector_remove() from the
    previous exercise, except that you always remove the last element,
    and you have to return it at the end of the function.
  */
  printf ("Please implement stack_grow!\n");
  return -100;
}


/*
 * This program reads lines from a file given on the command line (or
 * standard input if no argument is given). It makes a duplicate of
 * each line, and places the duplicate on a stack. After end of input,
 * it simply pops them all off the stack, prints them, and frees
 * them. This ends up printing the lines of a file in reverse.
 */
int main (int argc, char ** argv)
{
  char readbuf[BUFSIZE];
  Stack stack;
  char * msg;
  FILE * input;
  
  if (1 >= argc)
    input = stdin;
  else {
    input = fopen(argv[1], "r");
    if (NULL == input)
      err (EXIT_FAILURE, "%s", argv[1]);
  }
  
  stack_init (&stack);
  
  msg = NULL;
  while (NULL != fgets(readbuf, BUFSIZE, input)) {
    char * str = strdup(readbuf);
    if (NULL == str) {
      msg = "strdup failed";
      break;
    }
    if (0 != stack_push(&stack, str)) {
      msg = "stack_push failed";
      break;
    }
  }
  if (ferror(input)) {
    msg = "input error";
  }
  
  if (NULL != msg) {
    printf ("ERROR: %s\n", msg);
    stack_destroy (&stack);
    return 1;
  }
  
  while (NULL != (msg = stack_pop(&stack))) {
    printf ("%s", msg);
    free (msg);
  }
  
  stack_destroy (&stack);
  
  return 0;
}
