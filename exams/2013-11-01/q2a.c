void somefunction (unsigned int * arr, unsigned int N)
{
  unsigned int ii, jj, kk;
  for (ii = 0; ii < N; ++ii) {
    for (jj = ii+1; jj < N; ++jj) {
      printf ("[%3d][%3d]", ii, jj);
      for (kk = (arr[ii] + arr[jj]) % N; kk > 1; kk /= 2) {
        printf ("*");
      }
      printf ("\n");
    }
  }
}
