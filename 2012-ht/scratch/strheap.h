#ifndef ITADS_EX6_STRHEAP_H
#define ITADS_EX6_STRHEAP_H

#include <stdio.h>


/*
  This simple implementation has a fixed capacity.
*/
#define STRHEAP_CAPACITY  100


typedef struct {
  char * str[STRHEAP_CAPACITY+1]; /* num starts at [1] instead of [0] */
  size_t len;
} StrHeap;


StrHeap * strheap_new ();

void strheap_delete (StrHeap * heap);

void strheap_dump_dot (StrHeap * heap, const char * pre, const char * post, const char * label);

void strheap_insert (StrHeap * heap, char * str);

char * strheap_extract (StrHeap * heap);

void strheap_dump (StrHeap * heap, FILE * of);

void strheap_debug_on (void);

void strheap_debug_off (void);

#endif /* ITADS_EX6_STRHEAP_H */
