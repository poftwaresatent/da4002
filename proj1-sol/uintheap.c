#include "uintheap.h"

#include <err.h>
#include <stdlib.h>


static UintHeap * uintheap_new (uint cap)
{
  UintHeap * heap;
  if (NULL == (heap = calloc (1, sizeof *heap)))
    err (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  if (NULL == (heap->num = calloc (cap + 1, sizeof *heap->num)))
    err (EXIT_FAILURE, __FILE__": %s: calloc", __func__);
  heap->cap = cap;
  return heap;
}


static void bubble_up_max (UintHeap * heap, uint index)
{
  uint parent;
  
  parent = index / 2;
  while ((parent > 0) && (heap->num[index] > heap->num[parent])) {
    uint tmp;
    tmp = heap->num[index];
    heap->num[index] = heap->num[parent];
    heap->num[parent] = tmp;
    
    index = parent;
    parent = index / 2;
  }
}


static void bubble_down_max (UintHeap * heap, uint index)
{
  uint left, right, target;
  
  target = index;
  for (;;) {
    uint tmp;
    left = 2 * index;
    right = left + 1;
    if (left <= heap->len && heap->num[left] > heap->num[target])
      target = left;
    if (right <= heap->len && heap->num[right] > heap->num[target])
      target = right;
    if (target == index)
      return;
    tmp = heap->num[index];
    heap->num[index] = heap->num[target];
    heap->num[target] = tmp;
    
    index = target;
  }
}


static void bubble_up_min (UintHeap * heap, uint index)
{
  uint parent;
  
  parent = index / 2;
  while ((parent > 0) && (heap->num[index] < heap->num[parent])) {
    uint tmp;
    tmp = heap->num[index];
    heap->num[index] = heap->num[parent];
    heap->num[parent] = tmp;
    
    index = parent;
    parent = index / 2;
  }
}


static void bubble_down_min (UintHeap * heap, uint index)
{
  uint left, right, target;
  
  target = index;
  for (;;) {
    uint tmp;
    left = 2 * index;
    right = left + 1;
    if (left <= heap->len && heap->num[left] < heap->num[target])
      target = left;
    if (right <= heap->len && heap->num[right] < heap->num[target])
      target = right;
    if (target == index)
      return;
    tmp = heap->num[index];
    heap->num[index] = heap->num[target];
    heap->num[target] = tmp;
    
    index = target;
  }
}


UintHeap * uintheap_new_max (uint cap)
{
  UintHeap * heap = uintheap_new (cap);
  heap->bup = bubble_up_max;
  heap->bdown = bubble_down_max;
  return heap;
}


UintHeap * uintheap_new_min (uint cap)
{
  UintHeap * heap = uintheap_new (cap);
  heap->bup = bubble_up_min;
  heap->bdown = bubble_down_min;
  return heap;
}


void uintheap_delete (UintHeap * heap)
{
  free (heap->num);
  free (heap);
}


void uintheap_insert (UintHeap * heap, uint num)
{
  if (heap->cap <= heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: heap is full", __func__);

  heap->num[++heap->len] = num; /* pre-increment because num starts at [1] */
  heap->bup (heap, heap->len);
}


uint uintheap_extract (UintHeap * heap)
{
  uint num;

  if (0 == heap->len)
    errx (EXIT_FAILURE, __FILE__": %s: heap is empty", __func__);

  num = heap->num[1];		/* remember, we start at [1] instead of [0] */
  heap->num[1] = heap->num[heap->len--];
  if (0 < heap->len)
    heap->bdown (heap, 1);

  return num;
}
