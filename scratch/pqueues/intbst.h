#ifndef ITADS_EX6_PQUEUES_INTBST_H
#define ITADS_EX6_PQUEUES_INTBST_H


typedef struct intbst_s {
  int data;
  struct intbst_s * left;
  struct intbst_s * right;
} IntBST;


typedef void (*intbst_visit_fct_t)(IntBST*, void*);


/*
 * Helper function to create a new binary search tree.
 */
IntBST * intbst_new (int data);

/*
 * Free all the memory used by a tree and the items it stores. It
 * recursively frees all items at the given root and all its subtrees.
 */
void intbst_free (IntBST * root);

/*
 * Find an item that matches a given data, underneath the given root.
 *
 * This function returns a valid IntBST* if the data was found in the
 * tree, or NULL if it was not found. In both cases, if the parent
 * argument is non-NULL, the parent of the returned item will be
 * placed there. If the data was matched at the given root and parent
 * is non-NULL, then *parent will be set to NULL.
 */
IntBST * intbst_find (IntBST * root, int data, IntBST ** parent);

/*
 * Insert an item into a tree. It returns the root which should be
 * used in place of the given root (in most cases, this will simply be
 * the root that was given to the function). The way to call this
 * function is as follows:
 *
 *   root = intbst_ins (root, data);
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
 *  4. Otherwise, the data is already stored in the tree, so we do
 *     nothing.
 */
IntBST * intbst_ins (IntBST * root, int data);

/*
 * Remove an item from the tree. Similarly to intbst_ins, this
 * function returns a root to be used in place of the current one, and
 * is thus intended to be called like this:
 *
 *   root = intbst_rem (root, data);
 *
 * Where root is the root item of your binary search tree. In most
 * cases, the returned item will be just the root passed in as
 * argument. But if the given root matches the data and one or both of
 * its subtrees are NULL, then something else is returned.  This
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
 *  4. If the data matches and this root has only one subtree (either
 *     left or right), then use the "parent re-attachment trick" to
 *     skip over us.
 *
 *  5. If none of the above can be used, then we find the smallest
 *     child of the right subtree, and replace this root with that
 *     smallest child. It would work just as well to use the biggest
 *     child of the left subtree.
 */
IntBST * intbst_rem (IntBST * root, int data);


IntBST * intbst_rem_max (IntBST * root, IntBST ** maxitem);


/*
 * In-order traversal with a custom function to be applied for each
 * item. The given extra arg is passed to the fct for each item as
 * well, in case you need additional arguments to your custom
 * function.
 */
void intbst_in_order (IntBST * root, intbst_visit_fct_t fct, void * arg);

int intbst_print_dot (IntBST * tree, const char * filename, const char * label);


#endif /* ITADS_EX6_PQUEUES_INTBST_H */
