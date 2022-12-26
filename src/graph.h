#include <stdio.h>

#include "vertex.h"
#include "utils.h"

#ifndef GRAPH_COLOUR_GRAPH_H
#define GRAPH_COLOUR_GRAPH_H

typedef struct graph_s {
    vtxtree_t* vertices;
    int vertex_count;
} graph_t;

graph_t* create_graph(FILE* input_file, int max_name_len);

int write_graph(graph_t* graph, char* filename);

void colour_graph(graph_t* graph);

#endif // GRAPH_COLOUR_GRAPH_H
