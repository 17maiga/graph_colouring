#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree.h"
#include "vertex.h"

bstree_t* create_tree() {
    bstree_t* res = malloc(sizeof(bstree_t));
    res->value = NULL;
    res->lft = NULL;
    res->rgt = NULL;
    return res;
}

void delete_tree(bstree_t* tree) {
    if (tree != NULL) {
        delete_vertex(tree->value);
        delete_tree(tree->lft);
        delete_tree(tree->rgt);
    }
    free(tree);
}
