int calc (int i) {
  if (i <= 2) {
    return 0;
  }
  if (i == 3) {
    return 1;
  }
  return 2 * calc (i-3) - calc (i-2) + calc (i-1);
}

void print (int n) {
  int i;
  for (i = 1; i <= n; i++) {
    printf ("%d\n", calc (i));
  }
}
