#include "unsorted.h"
#include <err.h>
#include <stdlib.h>


void unsorted_insert (IntVec * vec, int num)
{
  intvec_ins (vec, vec->len, num);
}


int unsorted_extract (IntVec * vec)
{
  size_t pos;
  if ( ! intvec_findmax (vec, &pos))
    errx (EXIT_FAILURE, __FILE__": %s: intvec_findmax failed (empty vector?)", __func__);
  return intvec_rem (vec, pos);
}
