/*
  Notice: this function gets called on a tree that contains N items
*/
int recurse (Item * root)
{
  if (NULL == root) {
    return 0;
  }
  if (NULL != root->left) {
    if (NULL != root->right) {
      return recurse (root->left) + recurse (root->right);
    }
    return recurse (root->left);
  }
  if (NULL != root->right) {
    return recurse (root->right);
  }
  return 1;
}
