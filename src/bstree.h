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
bstree_t* create_tree();

/**
 * Frees a tree from memory.
 *
 * @param[in] tree
 */
void delete_tree(bstree_t* tree);

#endif // GRAPH_COLOUR_VTXTREE_H
