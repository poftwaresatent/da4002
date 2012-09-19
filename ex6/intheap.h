#ifndef ITADS_EX6_INTHEAP_H
#define ITADS_EX6_INTHEAP_H

#include <stdio.h>


/*
  This simple implementation has a fixed capacity.
*/
#define INTHEAP_CAPACITY  100


typedef struct {
  int num[INTHEAP_CAPACITY+1]; /* num starts at [1] instead of [0] */
  size_t len;
} IntHeap;


IntHeap * intheap_new ();

void intheap_delete (IntHeap * heap);

void intheap_dump_dot (IntHeap * heap, const char * pre, const char * post, const char * label);

void intheap_insert (IntHeap * heap, int num);

int intheap_extract (IntHeap * heap);

void intheap_dump (IntHeap * heap, FILE * of);

void intheap_debug_on (void);

void intheap_debug_off (void);

#endif /* ITADS_EX6_INTHEAP_H */
