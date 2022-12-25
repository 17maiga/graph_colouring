#include "vertex.h"

t_vertex* create_vertex(const char* name, const int neighbour_count)
{
    t_vertex* vertex = malloc(sizeof(t_vertex));

    vertex->name = name;
    vertex->colour = 0;
    vertex->neighbours = malloc(neighbour_count * sizeof(t_vertex));
}