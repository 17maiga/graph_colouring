#include <stdlib.h>
#include <string.h>

#include "graph.h"

graph_t* create_graph(FILE* input_file, int max_name_len) {
    graph_t* res = malloc(sizeof(graph_t));
    res->vertices = malloc(sizeof(vtxtree_t));
    res->vertices->value = NULL;
    res->vertices->lft = NULL;
    res->vertices->rgt = NULL;
    res->vertex_count = 0;
    int c, buflen = 0;
    char buffer[max_name_len];
    int status = 0;

    while ((c = fgetc(input_file)) != EOF) {
        switch (status) {
            case 0:
                if (c == '[') status = 1;
                break;
            case 1:
                if (c == ',' || c == ']') {
                    // Initialise the vertex
                    vertex_t* vertex = malloc(sizeof(vertex_t));
                    vertex->name_len = buflen;
                    vertex->name = malloc(buflen * sizeof(char));
                    strncpy(vertex->name, buffer, buflen);
                    buflen = 0;
                    // Insert the vertex into the graph's vertex tree
                    insert_vertex(res->vertices, vertex);
                    res->vertex_count++;
                    if (c == ']') status = 2;
                } else
                    buffer[buflen++] = c;
                break;
            // TODO: Finish reading the file
        }
    }
    if (status != 0) {
        printf("Error: File not properly formatted.\n");
        exit(1);
    }
    return res;
}
