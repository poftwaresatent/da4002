#ifndef ITADS_EX7_INTMBST_H
#define ITADS_EX7_INTMBST_H

#include "intvec.h"


typedef struct intmbst_s {
  IntVec * dvec;
  struct intmbst_s * left;
  struct intmbst_s * right;
} IntMBst;


typedef void (*intmbst_visit_fct_t)(IntMBst*, void*);


/*
 * Helper function to create a new binary search tree.
 */
IntMBst * intmbst_new (int data);

/*
 * Free all the memory used by a tree and the items it stores. It
 * recursively frees all items at the given root and all its subtrees.
 */
void intmbst_delete (IntMBst * root);

/*
 * Find an item that matches a given data, underneath the given root.
 *
 * This function returns a valid IntMBst* if the data was found in the
 * tree, or NULL if it was not found. In both cases, if the parent
 * argument is non-NULL, the parent of the returned item will be
 * placed there. If the data was matched at the given root and parent
 * is non-NULL, then *parent will be set to NULL.
 */
IntMBst * intmbst_find (IntMBst * root, int data, IntMBst ** parent);

/*
 * Insert an item into a tree. It returns the root which should be
 * used in place of the given root (in most cases, this will simply be
 * the root that was given to the function). The way to call this
 * function is as follows:
 *
 *   root = intmbst_ins (root, data);
 *
 * Where root is the root item of your binary search tree. Note that
 * passing root==NULL is valid, and indeed a convenient way to
 * initialize a tree with the first data item. This function does one
 * of four things:
 *
 *  1. If an empty slot has been found, create a new item for the
 *     data, to attach it as a new leaf to the tree.
 *
 *  2. If the given data is smaller than the one already stored in the
 *     root, then recurse into the left subtree for insertion there.
 *
 *  3. If the data is bigger than what we already have, recurse into
 *     the right subtree instead.
 *
 *  4. Otherwise, a corresponding number is already stored in an, and
 *     we append the new data there (for just integers, it would be
 *     sufficient to maintain a counter, but in general we'd keep
 *     various kinds of data attached to keys, so we simulate that
 *     case here by using an IntVec).
 */
IntMBst * intmbst_ins (IntMBst * root, int data);

/*
 * Remove an item from the tree. Similarly to intmbst_ins, this
 * function returns a root to be used in place of the current one, and
 * is thus intended to be called like this:
 *
 *   root = intmbst_rem (root, data);
 *
 * Where root is the root item of your binary search tree. In most
 * cases, the returned item will be just the root passed in as
 * argument. But if the given root matches the data and one or both of
 * its subtrees are NULL, then something else can be returned.  This
 * function does one of the following:
 *
 *  1. If the data is smaller than what is stored in this root,
 *     recurse into the left subtree.
 *
 *  2. If the data is bigger, then recurse to the right.
 *
 *  3. If the data matches and this root is a leaf (has no children),
 *     then simply remove it. NOTE that this is handled transparently
 *     by the code which handles possibility #4.
 *
 *  4. If the data matches and this root, has only one item left in
 *     its IntVec, and has only one subtree (either left or right),
 *     then use the "parent re-attachment trick" to skip over us.
 *
 *  5. If none of the above can be used, then we find the smallest
 *     child of the right subtree, and replace this root with that
 *     smallest child. It would work just as well to use the biggest
 *     child of the left subtree.
 */
IntMBst * intmbst_rem (IntMBst * root, int data);


IntMBst * intmbst_rem_max (IntMBst * root, int * maxdata);


/*
 * In-order traversal with a custom function to be applied for each
 * item. The given extra arg is passed to the fct for each item as
 * well, in case you need additional arguments to your custom
 * function.
 */
void intmbst_in_order (IntMBst * root, intmbst_visit_fct_t fct, void * arg);

int intmbst_print_dot (IntMBst * tree, const char * filename, const char * label);


#endif /* ITADS_EX7_INTMBST_H */
