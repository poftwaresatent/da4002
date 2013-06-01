#include <stdio.h>

#define KMAX 20

int main (int argc, char ** argv)
{
  struct {
    int v1, v3, v7, best;
  } tab[KMAX+1];
  int ii;
  
  tab[0].v1 = -1;;
  tab[0].v3 = -1;;
  tab[0].v7 = -1;;
  tab[0].best = 0;
  
  /*       12 | 12 12 12 | 12 | 1 2 3 */
  printf (" K | C1 C2 C3 |  V | best coin(s)\n"
	  "---+----------+----+-------------\n");
  
  for (ii = 1; ii <= KMAX; ++ii) {
    printf ("%2d | ", ii);
    
    tab[ii].v1 = 1 + tab[ii-1].best;
    tab[ii].best = tab[ii].v1;
    printf ("%2d ", tab[ii].v1);
    
    if (ii < 3) {
      tab[ii].v3 = -1;
      printf ("   ");
    }
    else {
      tab[ii].v3 = 1 + tab[ii-3].best;
      if (tab[ii].v3 < tab[ii].best)
	tab[ii].best = tab[ii].v3;
      printf ("%2d ", tab[ii].v3);
    }
    
    if (ii < 7) {
      tab[ii].v7 = -1;
      printf ("   | ");
    }
    else {
      tab[ii].v7 = 1 + tab[ii-7].best;
      if (tab[ii].v7 < tab[ii].best)
	tab[ii].best = tab[ii].v7;
      printf ("%2d | ", tab[ii].v7);
    }
    
    printf ("%2d | ", tab[ii].best);
    
    if (tab[ii].best == tab[ii].v1)
      printf ("1 ");
    if (tab[ii].best == tab[ii].v3)
      printf ("3 ");
    if (tab[ii].best == tab[ii].v7)
      printf ("7 ");
    
    printf ("\n");
  }
  
  return 0;
}
