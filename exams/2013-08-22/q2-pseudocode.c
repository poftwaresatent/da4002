typedef struct node_s {
  char data;
  struct node_s * cld;
  struct node_s * sib;
} Node;


typedef struct fifo_s {
  Node * node;
  struct fifo_s * next;
} Fifo;


/* Creates a Fifo item containing the given Node. */
Fifo * fifo_create (Node * node);

/* Returns the next Fifo item, or NULL when the Fifo is empty. */
Fifo * fifo_next (Fifo * head);


void method_one (Node * node)
{
  Fifo * head;
  Fifo * tail;
  head = fifo_create (node);
  tail = head;
  while (NULL != head) {
    printf ("%c", head->node->data);
    for (node = head->node->cld; NULL != node; node = node->sib) {
      tail->next = fifo_create (node);
      tail = tail->next;
    }
    head = fifo_next (head);
  }
}


void method_two (Node * node)
{
  Node * cld;
  for (cld = node->cld; NULL != cld; cld = cld->sib)
    method_two (cld);
  printf ("%c", node->data);
}


void method_three (Node * node)
{
  printf ("%c", node->data);
  for (node = node->cld; NULL != node; node = node->sib)
    method_three (node);
}
