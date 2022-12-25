#ifndef GRAPH_COLOUR_GRAPH_H
#define GRAPH_COLOUR_GRAPH_H

#include "vertex.h"

typedef struct s_graph {
    t_vertex** vertices;
} t_graph;

t_graph* create_graph();

int write_graph(t_graph* graph, char* filename);

void colour_graph(t_graph* graph);

#endif // GRAPH_COLOUR_GRAPH_H
