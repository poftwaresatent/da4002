int find (int * arr, int len, int num) {
  int low, high, mid;
  low = 0;
  high = len - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (arr[mid] < num) {
      high = mid - 1;
    }
    else if (arr[mid] > num) {
      low = mid + 1;
    }
    else {
      return mid;
    }
  }
  return -1;
}
