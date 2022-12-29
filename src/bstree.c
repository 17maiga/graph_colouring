#include <stdlib.h>

#include "bstree.h"

bstree_t* bstree_create() {
    bstree_t* res = malloc(sizeof(bstree_t));
    res->value = NULL;
    res->lft = NULL;
    res->rgt = NULL;
    return res;
}

void bstree_delete(bstree_t* tree) {
    if (tree != NULL) {
        // Assumes the tree's value does not need to be freed recursively. If a
        // tree is used with a value that does, this function needs to be
        // reimplemented for the value's specific data type (ex: vtxtree_delete)
        free(tree->value);
        bstree_delete(tree->lft);
        bstree_delete(tree->rgt);
    }
    free(tree);
}
