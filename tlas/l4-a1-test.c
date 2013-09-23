#include <stdio.h>
#include "l4-a1-vector.c"


int vector_test (void)
{
  Vector * vec;
  int ii, jj;
  
  vec = vector_create ();
  for (ii = -3; ii < 10; ++ii) {
    if (0 != vector_append (vec, ii)) {
      vector_destroy (vec);
      return -1;
    }
  }
  
  ii = -3;
  jj = 0;
  while (ii < 10 && jj < vec->len) {
    if (vec->arr[jj] != ii) {
      vector_destroy (vec);
      return -2;
    }
    ++ii;
    ++jj;
  }
  if (10 != ii) {
    vector_destroy (vec);
    return -3;
  }
  if (vec->len != jj) {
    vector_destroy (vec);
    return -4;
  }
  
  vector_rem_last (vec);
  
  ii = -3;
  jj = 0;
  while (ii < 9 && jj < vec->len) {
    if (vec->arr[jj] != ii) {
      vector_destroy (vec);
      return -5;
    }
    ++ii;
    ++jj;
  }
  if (9 != ii) {
    vector_destroy (vec);
    return -6;
  }
  if (vec->len != jj) {
    vector_destroy (vec);
    return -7;
  }
  
  vector_destroy (vec);
  
  return 0;
}


int main (int argc, char ** argv)
{
  printf ("%d\n", vector_test ());
  return 0;
}
