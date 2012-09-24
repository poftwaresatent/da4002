/*
 * pqvu.h
 *
 * Interface for priority queue implemented via an unsorted vector.
 */

#ifndef ITADS_EX7_PQVU_H
#define ITADS_EX7_PQVU_H

#include "intvec.h"

/*
 * Insert items by simply appending to the vector.
 */
void pqvu_insert (IntVec * vec, int num);

/*
 * Extract items by linearly searching for the maximum.
 */
int pqvu_extract (IntVec * vec);

#endif /* ITADS_EX7_PQVU_H */
