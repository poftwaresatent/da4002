#ifndef TEST_SORTING_ALGO_H
#define TEST_SORTING_ALGO_H

void test_create (int index, int ** input, int ** output);
int test_check (int const * input, int * output);
void test_destroy (int * input, int * output);

typedef struct sortfunc_s {
  char const * name;
  void (*func)(int *, int);
} sortfunc;

int test_runall (sortfunc const * funcs, int nfuncs);

#endif
