typedef struct node_s {
  char data;
  struct node_s * child;
  struct node_s * sibling;
} Node;


typedef struct fifo_s {
  Node * node;
  struct fifo_s * next;
} Fifo;


Fifo * fifo_create (Node * node)
{
  Fifo * fifo;
  fifo = calloc (1, sizeof *fifo);
  fifo->node = node;
  return fifo;
}


Fifo * fifo_next (Fifo * head)
{
  Fifo * next;
  next = head->next;
  free (head);
  return next;
}


void method_one (Node * root)
{
  Node * child;
  Fifo * head;
  Fifo * tail;
  head = fifo_create (root);
  tail = head;
  while (NULL != head) {
    printf ("%c", head->node->data);
    for (child = head->node->child; NULL != child; child = child->sibling) {
      tail->next = fifo_create (child);
      tail = tail->next;
    }
    head = fifo_next (head);
  }
}


void method_two (Node * node)
{
  Node * child;
  for (child = node->child; NULL != child; child = child->sibling)
    method_two (child);
  printf ("%c", node->data);
}


void method_three (Node * node)
{
  printf ("%c", node->data);
  for (node = node->child; NULL != node; node = node->sibling)
    method_three (node);
}
