#ifndef GRAPH_COLOUR_VERTEX_H
#define GRAPH_COLOUR_VERTEX_H

typedef struct s_vertex {
    char* name;
    int colour;
    struct s_vertex** neighbours;
} t_vertex;

t_vertex* create_vertex(const char* name, const int neighbour_count);

#endif // GRAPH_COLOUR_VERTEX_H
