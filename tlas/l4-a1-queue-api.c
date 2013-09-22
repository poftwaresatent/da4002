typedef struct queue_s {
  /* Fill this with the fields you need to implement a queue. */
} Queue;

/*
  Add functions as needed...
*/

/*
  This function should add the given integer "num" to the end of the queue.
*/
void queue_insert (Queue * queue, int num);

/*
  This function should return 1 when the queue is empty, and 0
  otherwise.
*/
int queue_empty (Queue * queue);

/*
  This function should remove the first item from the queue and
  return it. If the queue is empty, this function should return 0;
*/
int queue_extract (Queue * queue);
