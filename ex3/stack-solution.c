#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_CAPACITY    4
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
  for (str = *stack->arr; 0 < stack->len; --stack->len, ++str)
    free (str);
  free (stack->arr);
  stack->arr = NULL;
  stack->cap = 0;
}


/*
 * Utility function used internally by the stack when more memory is
 * required.
 *
 * \return zero on success.
 */
int stack_grow (Stack * stack)
{
  unsigned long newcap;
  char ** newarr;
  
  if (0 == stack->cap) {
    
    stack->arr = malloc (START_CAPACITY * sizeof(*stack->arr));
    if (NULL == stack->arr)
      return -1;
    
    stack->cap = START_CAPACITY;
    
    return 0;
  }
  
  newcap = 2 * stack->cap;
  newarr = realloc (stack->arr, newcap * sizeof(*stack->arr));
  if (NULL == newarr)
    return -1;
  stack->arr = newarr;
  stack->cap = newcap;
  
  return 0;
}


/*
 * User function to place a string onto the top of the stack. This is
 * essentially the same as vector_append() from the previous exercise.
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
  if (stack->len >= stack->cap) {
    if (0 != stack_grow (stack))
      return -1;
  }
  stack->arr[stack->len++] = str;
  return 0;
}


/*
 * User function to retrieve the string which is currently on top of
 * the stack. This is basically a combination of array lookup with
 * vector_remove of the last element.
 *
 * \note It is up to the user to free the returned string at the
 * appropriate moment.
 *
 * \return The topmost string, or NULL if the stack is empty.
 */
char * stack_pop (Stack * stack)
{
  if (stack->len > 0)
    return stack->arr[--(stack->len)];
  return NULL;
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
