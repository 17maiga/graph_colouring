#include <stdlib.h>
#include <string.h>

#include "graph.h"

// Structure

graph_t* create_graph() {
    graph_t* graph = malloc(sizeof(graph_t));
    graph->vertices = create_tree();
    graph->vertex_count = 0;
    return graph;
}

void delete_graph(graph_t* graph) {
    delete_tree(graph->vertices);
    free(graph);
}

// File operations

graph_t* read_graph(FILE* input_file, int max_name_len) {
    graph_t* graph = create_graph();
    int c, buflen = 0;
    char buffer[max_name_len];
    vertex_t* vertex_buffer = NULL;
    int status = STATUS_START;

    while ((c = fgetc(input_file)) != EOF && status != STATUS_DONE) {
        switch (status) {
            case STATUS_START:
                if (c == '[') status = STATUS_VERTEX_READ_NAME;
                break;
            case STATUS_VERTEX_READ_NAME:
                if (c == ',' || c == ']' || c == ':') {
                    // Initialise the vertex
                    vertex_buffer = create_vertex();
                    vertex_buffer->name_len = buflen;
                    vertex_buffer->name = malloc(buflen * sizeof(char));
                    strncpy(vertex_buffer->name, buffer, buflen);
                    buflen = 0;
                    // Insert the vertex into the graph's vertex tree
                    vtxtree_insert(graph->vertices, vertex_buffer);
                    graph->vertex_count++;
                    if (c == ':') {
                        status = STATUS_VERTEX_READ_COLOUR;
                        break;
                    }
                    vertex_buffer = NULL;
                    if (c == ']') status = STATUS_VERTEX_DONE;
                } else buffer[buflen++] = c;
                break;
            case STATUS_VERTEX_READ_COLOUR:
                if (c == ',' || c == ']') {
                    char colourchars[buflen];
                    strncpy(colourchars, buffer, buflen);
                    int colour;
                    sscanf(colourchars, "%d", &colour);
                    vertex_buffer->colour = colour;
                    vertex_buffer = NULL;
                } else buffer[buflen++] = c;
                break;
            case STATUS_VERTEX_DONE:
                // Skip the grapht of the line
                while (c != '\n' && c != EOF) c = fgetc(input_file);
                if (c == EOF) {
                    status = STATUS_DONE;
                    break;
                }
                // Find the next '[' character
                while (c != '[' && c != EOF) c = fgetc(input_file);
                if (c == EOF) {
                    status = STATUS_DONE;
                    break;
                }
                status = STATUS_EDGES_READ;
                break;
            case STATUS_EDGES_READ:
                if (c == '(') {
                    status = STATUS_EDGE_READ_START;
                }
                if (c == ']')
                    status = STATUS_DONE;
                break;
            case STATUS_EDGE_READ_START:
                if (c == ',') {
                    char name[buflen];
                    strncpy(name, buffer, buflen);
                    buflen = 0;
                    vertex_buffer = vtxtree_get(graph->vertices, name);
                    status = STATUS_EDGE_READ_END;
                } else buffer[buflen++] = c;
                break;
            case STATUS_EDGE_READ_END:
                if (c == ')') {
                    char name[buflen];
                    strncpy(name, buffer, buflen);
                    buflen = 0;
                    vertex_t* vertex = vtxtree_get(graph->vertices, name);
                    create_edge(vertex, vertex_buffer);
                    status = STATUS_EDGES_READ;
                } else buffer[buflen++] = c;
                break;
        }
    }
    if (status != STATUS_DONE) {
        printf("Error: read_graph: Input file not complete.\n");
        exit(1);
    }
    return graph;
}

void write_graph(FILE* output_file, graph_t* graph) {
    fprintf(output_file, "%d\n[", graph->vertex_count);
    vertex_t** vertices = vtxtree_infix(graph->vertices, graph->vertex_count);
    for (int i = 0; i < graph->vertex_count-1; i++) {
        fprintf(output_file, "%s:%d,", vertices[i]->name, vertices[i]->colour);
    }
    fprintf(output_file, "%s:%d]\n[", vertices[graph->vertex_count-1]->name,
            vertices[graph->vertex_count-1]->colour);
    for (int i = 0; i < graph->vertex_count; i++) {
        vtx_print_edges(output_file, vertices[i]);
    }
    fprintf(output_file, "]\n");
}
