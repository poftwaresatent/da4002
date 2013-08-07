typedef struct node_s {
  char data;
  struct node_s * cld, * sbl;
} Node;


void function_one (Node * nn) {
  Fifo * fifo = fifo_create ();
  while (NULL != nn) {
    printf ("%c", nn->data);
    for (nn = nn->cld; NULL != nn; nn = nn->sbl) {
      fifo_append (fifo, nn);
    }
    nn = fifo_extract (fifo);
  }
  fifo_destroy (fifo);
}


void function_two (Node * nn) {
  printf ("%c", nn->data);
  for (nn = nn->cld; NULL != nn; nn = nn->sbl) {
    function_two (nn);
  }
}


void function_three (Node * nn) {
  Node * tmp;
  for (tmp = nn->cld; NULL != tmp; tmp = tmp->sbl) {
    function_three (tmp);
  }
  printf ("%c", nn->data);
}
