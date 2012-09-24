/*
 * pqvu.c
 *
 * Implementation of vector-based priority queue (unsorted versions)
 */

#include "pqvu.h"
#include <err.h>
#include <stdlib.h>


void pqvu_insert (IntVec * vec, int num)
{
  intvec_ins (vec, vec->len, num);
}


int pqvu_extract (IntVec * vec)
{
  size_t pos;
  if ( ! intvec_findmax (vec, &pos))
    errx (EXIT_FAILURE, __FILE__": %s: intvec_findmax failed (empty vector?)", __func__);
  return intvec_rem (vec, pos);
}
