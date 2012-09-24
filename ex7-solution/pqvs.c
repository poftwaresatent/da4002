#include "pqvs.h"


void pqvs_insert (IntVec * vec, int num)
{
  intvec_ins_asc (vec, num);
}


int pqvs_extract (IntVec * vec)
{
  return intvec_rem (vec, vec->len - 1);
}
