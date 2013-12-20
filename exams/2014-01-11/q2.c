int function_A (ItemA * item)
{
  int nn;
  nn = item->data;
  for (item = item->child; NULL != item; item = item->sibling) {
    nn += function_A (item);
  }
  return nn;
}


void function_B (ListB * list)
{
  ItemB * item;
  int nn = 0;
  for (item = list->tail; NULL != item; item = item->prev) {
    item->data = nn++;
  }
}


void function_C (ListC * list)
{
  ItemC * item;
  if (NULL != list->head) {
    for (item = list->tail; list->head != item; item = item->prev) {
      printf ("  %d", item->data);
    }
    printf ("  %d", list->head->data);
  }
}


void function_D (ItemD * item)
{
  if (NULL != item) {
    printf ("  %d", item->data);
    function_D (item->left);
    function_D (item->right);
  }
}
