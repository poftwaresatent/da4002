#ifndef ITADS_EX7_INTVEC_H
#define ITADS_EX7_INTVEC_H

#include <stdlib.h>
#include <stdio.h>


typedef struct {
  int * arr;
  size_t len;
  size_t cap;
} IntVec;


IntVec * intvec_new (size_t startcap);

void intvec_delete (IntVec * vec);

void intvec_ins (IntVec * vec, size_t pos, int value);

int intvec_rem (IntVec * vec, size_t pos);

size_t intvec_ins_asc (IntVec * vec, int num);

size_t intvec_ins_desc (IntVec * vec, int num);

int intvec_linsearch (IntVec * vec, int num, size_t * pos);

int intvec_findmin (IntVec * vec, size_t * pos);

int intvec_findmax (IntVec * vec, size_t * pos);

int intvec_binsearch (IntVec * vec, int num, size_t * pos);

void intvec_dump (IntVec * vec, char * name, FILE * of);

int intvec_nonempty (IntVec * vec);

#endif /* ITADS_EX7_INTVEC_H */
