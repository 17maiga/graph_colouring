#include <stdlib.h>

#include "vertex.h"

vertex_t* create_vertex(char* name, const int neighbour_count) {
    vertex_t* vertex = malloc(sizeof(vertex_t));

    vertex->name = name;
    vertex->colour = 0;
    vertex->neighbours = malloc(neighbour_count * sizeof(vertex_t));
}
