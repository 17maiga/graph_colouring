#ifndef GRAPH_COLOUR_VTXTREE_H
#define GRAPH_COLOUR_VTXTREE_H

typedef struct bstree_s {
    void* value;
    struct bstree_s* lft;
    struct bstree_s* rgt;
} bstree_t;

/**
 * Creates an empty binary search tree.
 *
 * @param[out] tree;
 */
bstree_t* bstree_create();

/**
 * Frees a binary search tree from memory.
 * Assumes the tree's value does not need to be freed recursively. If a tree is
 * used with a value that does, this function needs to be reimplemented for the
 * value's specific data type (ex: vtxtree_delete).
 *
 * @param[in] tree
 */
void bstree_delete(bstree_t* tree);

#endif // GRAPH_COLOUR_VTXTREE_H
