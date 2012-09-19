#ifndef ITADS_EX6_STR_MIN_HEAP_H
#define ITADS_EX6_STR_MIN_HEAP_H

/* #include <stdio.h> */
/* #include <err.h> */
/* #include <stdlib.h> */
/* #include <string.h> */


/* /\* */
/*   This simple implementation has a fixed capacity. */
/* *\/ */
/* #define CAPACITY  100 */
/* #define BUFSIZE  1024 */


typedef struct {
  char * str[CAPACITY+1];	/* num starts at [1] instead of [0] */
  size_t len;
} StrHeap;


void strheap_new (StrHeap * heap);
void strheap_delete (StrHeap * heap);
void strheap_strheap_dump_dot (StrHeap * heap, char * post, char * label);
void strheap_insert (StrHeap * heap, char * str);
char * strheap_extract (StrHeap * heap);
void strheap_dump (StrHeap * heap, FILE * of);

#endif /* ITADS_EX6_STR_MIN_HEAP_H */
