#ifndef ITADS_EX6_INTHEAP_H
#define ITADS_EX6_INTHEAP_H

#include <stdio.h>


typedef struct {
  int * num;			/* num starts at [1] instead of [0] */
  size_t len;
  size_t cap;
} IntHeap;


IntHeap * intheap_new (size_t cap);

void intheap_delete (IntHeap * heap);

void intheap_dump_dot (IntHeap * heap, const char * pre, const char * post, const char * label);

void intheap_insert (IntHeap * heap, int num);

int intheap_extract (IntHeap * heap);

int intheap_nonempty (IntHeap * heap);

void intheap_dump (IntHeap * heap, FILE * of);

void intheap_debug_on (void);

void intheap_debug_off (void);

#endif /* ITADS_EX6_INTHEAP_H */
