Item * find (Item * item, int data)
{
  while (NULL != item) {
    if (data < item->data) {
      item = item->left;
    }
    else if (data > item->data) {
      item = item->right;
    }
    else {
      break;
    }
  }
  return item;
}
