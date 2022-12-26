#include "vertex.h"

#ifndef GRAPH_COLOR_UTILS_H
#define GRAPH_COLOR_UTILS_H

typedef struct vtxtree_s {
    vertex_t* value;
    struct vtxtree_s* lft;
    struct vtxtree_s* rgt;
} vtxtree_t;

void insert_vertex(vtxtree_t* tree, vertex_t* vertex);

void usage();

#endif // GRAPH_COLOR_UTILS_H
