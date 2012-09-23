#include "pqbst.h"
#include <stdlib.h>
#include <err.h>


PqBST * pqbst_new (void)
{
  PqBST * pq;
  if (NULL == (pq = calloc (1, sizeof *pq)))
    err (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  return pq;
}


void pqbst_delete (PqBST * pq)
{
  intmbst_delete (pq->root);
  free (pq);
}


void pqbst_insert (PqBST *pq, int num)
{
  pq->root = intmbst_ins (pq->root, num);
}


int pqbst_extract (PqBST *pq)
{
  int result;
  if (NULL == pq->root)
    errx (EXIT_FAILURE, __FILE__": %s: empty tree", __func__);
  pq->root = intmbst_rem_max (pq->root, &result);
  return result;
}


int pqbst_nonempty (PqBST *pq)
{
  return NULL == pq->root ? 0 : 1;
}
