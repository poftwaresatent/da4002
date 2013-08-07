#ifndef ITADS_PROJ1_UINTHEAP_H
#define ITADS_PROJ1_UINTHEAP_H


typedef unsigned int uint;

typedef struct uintheap_s{
  uint * num;
  uint cap;
  uint len;
  void (*bup) (struct uintheap_s *, uint);
  void (*bdown) (struct uintheap_s *, uint);
} UintHeap;


UintHeap * uintheap_new_max (uint cap);
UintHeap * uintheap_new_min (uint cap);
void uintheap_delete (UintHeap * heap);
void uintheap_insert (UintHeap * heap, uint num);
uint uintheap_extract (UintHeap * heap);

#endif /* ITADS_PROJ1_UINTHEAP_H */
