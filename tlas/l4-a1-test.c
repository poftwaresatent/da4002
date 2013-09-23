#include <stdio.h>
#include "l4-a1-vector.c"
#include "l4-a1-list.c"


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


int list_test (void)
{
  static int const data[] = { 3, 14, 15, 92 };
  int ii;
  List * list;
  Item * item;
  
  list = list_create ();
  for (ii = 0; ii < sizeof(data)/sizeof(*data); ++ii) {
    if (0 != list_append (list, data[ii])) {
      list_destroy (list);
      return -1;
    }
  }
  
  ii = 0;
  item = list->head;
  while (ii < sizeof(data)/sizeof(*data) && NULL != item) {
    if (data[ii] != item->data) {
      list_destroy (list);
      return -2;
    }
    ++ii;
    item = item->next;
  }
  if (ii != sizeof(data)/sizeof(*data)) {
    list_destroy (list);
    return -3;
  }
  if (NULL != item) {
    list_destroy (list);
    return -4;
  }
  
  list_rem_head (list);
  
  ii = 1;
  item = list->head;
  while (ii < sizeof(data)/sizeof(*data) && NULL != item) {
    if (data[ii] != item->data) {
      list_destroy (list);
      return -5;
    }
    ++ii;
    item = item->next;
  }
  if (ii != sizeof(data)/sizeof(*data)) {
    list_destroy (list);
    return -6;
  }
  if (NULL != item) {
    list_destroy (list);
    return -7;
  }
  
  list_destroy (list);
  
  return 0;
}


int main (int argc, char ** argv)
{
  printf ("vector_test: %d\n", vector_test ());
  printf ("list_test: %d\n", list_test ());
  return 0;
}
