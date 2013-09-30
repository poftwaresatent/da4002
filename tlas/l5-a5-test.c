#include "l5-a5-preamble.c"
#include "l5-a5-code.c"
#include <err.h>
#include <stdio.h>


Memo * memo_create ()
{
  Memo * memo;
  memo = calloc (1, sizeof *memo);
  if (NULL == memo) {
    err (EXIT_FAILURE, __FILE__":%s: calloc", __func__);
  }
  
  /*
    The devil is in the details: fibMemo() does not have a
    termination condition, it is implicitly provided here by
    initializing with the first two entries of the memo.
  */
  memo->len = 2;
  memo->arr = malloc (2 * sizeof *memo->arr);
  memo->arr[0] = 1;
  memo->arr[1] = 1;
  
  return memo;
}


void memo_destroy (Memo * memo)
{
  free (memo->arr);
  free (memo);
}


int memo_get (Memo * memo, int ii)
{
  ////  fprintf (stderr, "%s %d", __func__, ii);
  if (ii >= memo->len) {
    ////    fprintf (stderr, " [grow from %d]", memo->len);
    memo->arr = realloc (memo->arr, ii + 1);
    if (NULL == memo->arr) {
      err (EXIT_FAILURE, __FILE__":%s: realloc", __func__);
    }
    for (/**/; memo->len <= ii; ++memo->len) {
      memo->arr[memo->len] = -1;
    }
  }
  ////  fprintf (stderr, " -> %d\n", memo->arr[ii]);
  return memo->arr[ii];
}


void memo_set (Memo * memo, int ii, int fi)
{
  ////  fprintf (stderr, "%s %d %d", __func__, ii, fi);
  if (ii >= memo->len) {
    ////    fprintf (stderr, " [grow from %d]", memo->len);
    memo->arr = realloc (memo->arr, ii+1);
    if (NULL == memo->arr) {
      err (EXIT_FAILURE, __FILE__":%s: realloc", __func__);
    }
    for (/**/; memo->len <= ii; ++memo->len) {
      memo->arr[memo->len] = -1;
    }
  }
  ////  fprintf (stderr, "\n");
  memo->arr[ii] = fi;
}


int main (int argc, char ** argv)
{
  int ii;
  for (ii = 0; ii <= 10; ++ii) {
    printf ("  %d\n", fibMemo (ii));
  }
  return 0;
}
