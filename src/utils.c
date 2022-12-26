#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void insert_vertex(vtxtree_t* tree, vertex_t* vertex) {
    if (tree->value == NULL) {
        tree->value = vertex;
    } else if (strcmp(vertex->name, tree->value->name) < 0) {
        if (tree->lft == NULL) {
            tree->lft = malloc(sizeof(vtxtree_t));
            tree->lft->value = NULL;
            tree->lft->lft = NULL;
            tree->lft->rgt = NULL;
        }
        insert_vertex(tree->lft, vertex);
    } else if (strcmp(vertex->name, tree->value->name) > 0) {
        if (tree->rgt == NULL) {
            tree->rgt = malloc(sizeof(vtxtree_t));
            tree->rgt->value = NULL;
            tree->rgt->lft = NULL;
            tree->rgt->rgt = NULL;
        }
        insert_vertex(tree->rgt, vertex);
    } else {
        printf("Error: Found a duplicate name: %s\n", vertex->name);
        exit(EXIT_FAILURE);
    }
}

void usage() {
    printf("Usage: graph_color <filename>");
    exit(EXIT_FAILURE);
}
