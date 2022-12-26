#ifndef GRAPH_COLOUR_VERTEX_H
#define GRAPH_COLOUR_VERTEX_H

typedef struct vertex_s {
    char* name;
    int name_len;
    int colour;
    struct vertex_s** neighbours;
    int neighbours_len;
} vertex_t;

vertex_t* create_vertex(char* name, const int neighbour_count);

#endif // GRAPH_COLOUR_VERTEX_H
