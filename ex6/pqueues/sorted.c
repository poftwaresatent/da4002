#include "sorted.h"


void sorted_insert (IntVec * vec, int num)
{
  intvec_ins_desc (vec, num);
}


int sorted_extract (IntVec * vec)
{
  return intvec_rem (vec, 0);
}
