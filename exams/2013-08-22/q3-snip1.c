int algo_a (Item * head) {
  if (NULL == head) {
    return 0;
  }
  if (head->num % 2) {
    return algo_a (head->next);
  }
  return 1 + algo_a (head->next);
}
