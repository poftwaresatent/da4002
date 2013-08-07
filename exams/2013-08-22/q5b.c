void isort (int * arr, int len) {
  int ii, jj;
  for (ii = 1; ii < len; ++ii) {
    for (jj = ii; jj > 0; --jj) {
      if (arr[ii] >= arr[jj-1]) {
	break;
      }
      arr[jj] = arr[jj-1];
    }
    arr[jj] = arr[ii];
  }
}
