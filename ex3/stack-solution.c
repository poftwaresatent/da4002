#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_CAPACITY    4
#define BUFSIZE        1024


typedef struct stack_s {
  char ** arr;
  unsigned long len;
  unsigned long cap;
} Stack;


void stack_init (Stack * stack)
{
  stack->arr = NULL;
  stack->len = 0;
  stack->cap = 0;
}


void stack_destroy (Stack * stack)
{
  char *str;
  for (str = stack->arr; 0 < stack->len; --stack->len, ++str)
    free (str);
  free (stack->arr);
  stack->arr = NULL;
  stack->cap = 0;
}


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
  
  newarr = malloc (newcap * sizeof(*stack->arr));
  if (NULL == newarr)
    return -1;
  
  memcpy (newarr, stack->arr, stack->len * sizeof(*stack->arr));
  free (stack->arr);
  stack->arr = newarr;
  stack->cap = newcap;
  
  return 0;
}


int stack_push (Stack * stack, char * str)
{
  if (stack->len >= stack->cap) {
    if (0 != stack_grow (stack))
      return -1;
  }
  stack->arr[stack->len++] = str;
  return 0;
}


char * stack_pop (Stack * stack)
{
  if (stack->len > 0)
    return stack->arr[--(stack->len)];
  return NULL;
}


int main (int argc, char ** argv)
{
  char readbuf[BUFSIZE];
  Stack stack;
  
  stack_init (&stack);

  while (NULL != fgets(readbuf, BUFSIZE, stdin)) {
    
  }
  if (ferror(stdin)) {
    printf ("input error\n");
  }
  else {
    char * str;
#warning 'continue here...'
  }
  
  stack_destroy (&stack);
  
  return 0;
}
