void append (List * list, int data)
{
  Item * item;
  
  item = malloc (sizeof *item);
  if (NULL == item) {
    err (EXIT_FAILURE, "%s: malloc", __func__);
  }
  item->data = data;
  
  if (NULL == list->head) {
    list->head = item;
    list->tail = item;
    item->next = item;
  }
  else {
    list->tail->next = item;
    list->tail = item;
    item->next = list->head;
  }
}
