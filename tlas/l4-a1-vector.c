#include <stdlib.h>
#include <string.h>

#define START_CAPACITY 4


typedef struct vector_s {
  int * arr;
  unsigned long len;
  unsigned long cap;
} Vector;


Vector * vector_create ()
{
  Vector * vec;
  vec = calloc (1, sizeof *vec);
  return vec;
}


void vector_destroy (Vector * vec)
{
  free (vec->arr);
  free (vec);
}


int vector_grow (Vector * vec)
{
  unsigned long newcap;
  int * newarr;
  
  if (0 == vec->cap) {
    vec->arr = malloc (START_CAPACITY * (sizeof *vec->arr));
    if (NULL == vec->arr) {
      return -1;
    }
    vec->cap = START_CAPACITY;
    return 0;
  }
  
  newcap = 2 * vec->cap;
  newarr = realloc (vec->arr, newcap * (sizeof *vec->arr));
  if (NULL == newarr) {
    return -1;
  }
  vec->arr = newarr;
  vec->cap = newcap;
  
  return 0;
}


int vector_append (Vector * vec, int value)
{
  if (vec->len >= vec->cap) {
    if (0 != vector_grow (vec)) {
      return -1;
    }
  }
  vec->arr[vec->len++] = value;
  return 0;
}


void vector_rem_last (Vector * vec)
{
  --(vec->len);
}
