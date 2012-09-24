#include "toto.h"

void toto_init (Bar * tab, int len)
{
  int ii;
  for (ii = 0; ii < len; ++ii) {
    tab[ii].num = ii+1;
    tab[ii].letter = 'A' + ii % 26;
  }
}
