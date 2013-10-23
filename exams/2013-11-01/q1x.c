void print (Item * item)
{
  Item * it;
  printf ("%d\n", item->data);
  for (it = item->child;
       NULL != it;
       it = it->sibling) {
    print (it);
  }
}
