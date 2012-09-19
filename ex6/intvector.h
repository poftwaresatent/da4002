#ifndef ITADS_EX6_INTVECTOR_H
#define ITADS_EX6_INTVECTOR_H

#include <stdlib.h>
#include <stdio.h>


typedef struct {
  int * arr;
  size_t len;
  size_t cap;
} IntVector;


IntVector * intvector_new ();

void intvector_delete (IntVector * vec);

void intvector_ins (IntVector * vec, size_t pos, int value);

int intvector_rem (IntVector * vec, size_t pos);

size_t intvector_ins_asc (IntVector * vec, int num);

size_t intvector_ins_desc (IntVector * vec, int num);

int intvector_linsearch (IntVector * vec, int num, size_t * pos);

int intvector_findmin (IntVector * vec, size_t * pos);

int intvector_findmax (IntVector * vec, size_t * pos);

int intvector_binsearch (IntVector * vec, int num, size_t * pos);

void intvector_dump (IntVector * vec, char * name, FILE * of);

#endif /* ITADS_EX6_INTVECTOR_H */
