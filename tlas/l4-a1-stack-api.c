typedef struct stack_s {
  /* Fill this with the fields you need to implement a stack. */
} Stack;

/*
  Add functions as needed...
*/

/*
  This function should grow the stack by the given integer "num".
*/
void stack_push (Stack * stack, int num);

/*
  This function should return 1 when the stack is empty, and 0
  otherwise.
*/
int stack_empty (Stack * stack);

/*
  This function should remove the topmost item from the stack and
  return it. If the stack is empty, this function should return 0;
*/
int stack_pop (Stack * stack);
