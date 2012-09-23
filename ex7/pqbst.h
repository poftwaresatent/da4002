#ifndef ITADS_EX7_PQBST_H
#define ITADS_EX7_PQBST_H

#include "intmbst.h"

typedef struct {
  IntMBst * root;
} PqBST;

PqBST * pqbst_new (void);

void pqbst_delete (PqBST * pq);

void pqbst_insert (PqBST *pq, int num);

int pqbst_extract (PqBST *pq);

int pqbst_nonempty (PqBST *pq);

#endif /* ITADS_EX7_PQBST_H */
