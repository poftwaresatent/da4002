int algo_b (Item * head) {
  int res;
  Item * ii, * jj;
  res = 0;
  for (ii = head; NULL != ii; ii = ii->next) {
    for (jj = ii->next; NULL != jj; jj = jj->next) {
      res += ii->num * jj->num;
    }
  }
  return res;
}
