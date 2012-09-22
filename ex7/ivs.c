#include "ivs.h"


void ivs_insert (IntVec * vec, int num)
{
  intvec_ins_desc (vec, num);
}


int ivs_extract (IntVec * vec)
{
  return intvec_rem (vec, 0);
}
