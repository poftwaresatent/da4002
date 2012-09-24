/*
 * pqvs.h
 *
 * Interface for priority queue implemented using a sorted vector.
 */

#ifndef ITADS_EX7_PQVS_H
#define ITADS_EX7_PQVS_H

#include "intvec.h"

/*
 * Insert an item by finding where to place it such that the vector
 * remains sorted.
 */
void pqvs_insert (IntVec * vec, int num);

/*
 * Extract an item by simply taking it off the end. We can do this
 * because pqvs_insert ensures that the biggest item is always last in
 * the vector.
 */
int pqvs_extract (IntVec * vec);

#endif /* ITADS_EX7_PQVS_H */
