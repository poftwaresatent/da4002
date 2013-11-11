#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/uio.h>
#include <sys/time.h>


/***************************************************
  Merge sort implementation
***************************************************/


static void merge (int * arr, int * tmp, size_t beg, size_t mid, size_t end)
{
  size_t ii = beg;
  size_t jj = mid;
  size_t kk = beg;
  
  while (ii < mid && jj < end) {
    if (arr[ii] < arr[jj]) {
      tmp[kk++] = arr[ii++];
    }
    else {
      tmp[kk++] = arr[jj++];
    }
  }
  
  while (ii < mid) {
    tmp[kk++] = arr[ii++];
  }
  while (jj < end) {
    tmp[kk++] = arr[jj++];
  }
  
  for (ii = beg; ii < end; ++ii) {
    arr[ii] = tmp[ii];
  }
}


static void msort_rec (int * arr, int * tmp, int beg, int end)
{
  size_t len, mid;
  
  len = end - beg;
  if (1 >= len) {
    return;
  }
  
  mid = beg + len / 2;
  msort_rec (arr, tmp, beg, mid);
  msort_rec (arr, tmp, mid, end);
  merge (arr, tmp, beg, mid, end);
}


static void merge_sort (int * arr, int len)
{
  int * tmp = malloc (len * sizeof(int));
  if (NULL == tmp) {
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  }
  msort_rec (arr, tmp, 0, len);
  free (tmp);
}


/***************************************************
  Declarations of utility functions used in the benchmark. They are
  defined after the main function. You do not need to understand how
  they work, just use them in your benchmarks by copy-pasting.
***************************************************/

/* Returns a random integer in the specified range. */
static int random_int (int minval, int maxval);

/* Returns a freshly allocated array with len random integers from the
   specified range. The returned array has to be freed at the end of
   the program. */
static int * random_array (int minval, int maxval, size_t len);


static void test_create (int index, int ** input, int ** output);
static int test_check (int const * input, int * output);
static void test_destroy (int * input, int * output);


/***************************************************/

int main (int argc, char ** argv)
{
  int * input;
  int * output;
  int ii, pass;
  
  pass = 1;
  for (ii = 0; ii < 10; ++ii) {
    test_create (ii, &input, &output);
    merge_sort (output, 10);
    if ( ! test_check (input, output)) {
      pass = 0;
    }
    test_destroy (input, output);
  }
  
  return pass ? 0 : 1;
}


/***************************************************/


void test_create (int index, int ** input, int ** output)
{
  int jj;
  
  if (0 == index) {
    *input = malloc (10 * sizeof(int));
    if (NULL == output) {
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    }
    for (jj = 0; jj < 10; ++jj) {
      (*input)[jj] = jj;
    }
  }
  else if (1 == index) {
    *input = malloc (10 * sizeof(int));
    if (NULL == output) {
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    }
    for (jj = 0; jj < 10; ++jj) {
      (*input)[jj] = 9 - jj;
    }
  }
  else if (2 == index) {
    *input = malloc (10 * sizeof(int));
    if (NULL == output) {
      err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
    }
    for (jj = 0; jj < 10; ++jj) {
      (*input)[jj] = jj % 2;
    }
  }
  else {
    *input = random_array (0, 9, 10);
  }
  
  *output = malloc (10 * sizeof(int));
  if (NULL == output) {
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  }
  memcpy (*output, *input, 10 * sizeof(int));
}


int test_check (int const * input, int * output)
{
  int jj, kk, pass;
  
  printf ("check [%d", input[0]);
  for (jj = 1; jj < 10; ++jj) {
    printf (" %d", input[jj]);
  }
  printf ("] -> [%d", output[0]);
  for (jj = 1; jj < 10; ++jj) {
    printf (" %d", output[jj]);
  }
  printf ("]: ");
  
  pass = 1;
  for (jj = 1; jj < 10; ++jj) {
    if (output[jj-1] > output[jj]) {
      pass = 0;
      printf ("FAILED output[%d] = %d > output[%d] = %d)\n",
	      jj-1, output[jj-1], jj, output[jj]);
      break;
    }
  }
  
  if (pass) {
    for (jj = 0; jj < 10; ++jj) {
      for (kk = 0; kk < 10; ++kk) {
	if (output[kk] >= 0 && output[kk] == input[jj]) {
	  output[kk] = -1;
	  break;
	}
      }
      if (kk >= 10) {
	pass = 0;
	printf ("FAILED input[%d] = %d not found (sufficiently often) in output\n",
		jj, input[jj]);
	break;
      }
    }
  }
  
  if (pass) {
    printf ("passed\n");
  }
  
  return pass;
}


void test_destroy (int * input, int * output)
{
  free (input);
  free (output);
}


int random_int (int minval, int maxval)
{
  static int fd = -1;
  unsigned int delta, tmp, mask;
  
  if (0 > fd && 0 > (fd = open ("/dev/urandom", O_RDONLY))) {
    err (EXIT_FAILURE, __FILE__": %s: open /dev/urandom", __func__);
  }
  
  if (maxval < minval) {
    tmp = minval;
    minval = maxval;
    maxval = tmp;
  }
  if (0 == (delta = maxval - minval)) {
    return minval;
  }
  
  for (tmp = 1 << (8 * sizeof(int) - 1); 0 == (tmp & delta); tmp >>= 1) {
    /* nop */;
  }
  for (mask = tmp; 0 != tmp; tmp >>= 1) {
    mask |= tmp;
  }
  
  for (;;) {
    if (sizeof(int) != read (fd, &tmp, sizeof(int))) {
      err (EXIT_FAILURE, __FILE__": %s: read /dev/urandom", __func__);
    }
    tmp &= mask;
    if (tmp <= delta) {
      break;
    }
  }
  
  return minval + tmp;
}


int * random_array (int minval, int maxval, size_t len)
{
  int * arr;
  int * ii;
  
  arr = malloc (len * sizeof(int));
  if (NULL == arr) {
    err (EXIT_FAILURE, __FILE__": %s: malloc", __func__);
  }
  
  for (ii = arr; len > 0; ++ii, --len) {
    *ii = random_int (minval, maxval);
  }
  
  return arr;
}
