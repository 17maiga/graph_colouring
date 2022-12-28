#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

// Structure

graph_t* gph_create() {
    graph_t* graph = malloc(sizeof(graph_t));
    graph->vertices = bstree_create();
    graph->vertex_count = 0;
    return graph;
}

void gph_delete(graph_t* graph) {
    vtxbstree_delete(graph->vertices);
    free(graph);
}

// Linked list interaction

llist_t* gphllist_insert(llist_t* list, graph_t* graph) {
    if (list == NULL)
        list = llist_create();
    if (list->value == NULL)
        list->value = graph;
    else
        list->next = gphllist_insert(list->next, graph);
    return list;
}

graph_t* gphllist_get(llist_t* list, int index) {
    if (list == NULL || list->value == NULL) {
        printf("Error: gphllist_get: No graph at index: %d\n", index);
        exit(EXIT_FAILURE);
    }

    if (index == 0)
        return (graph_t*) list->value;

    return gphllist_get(list->next, index-1);
}

void gphllist_delete(llist_t* list) {
    if (list != NULL) {
        gph_delete(list->value);
        gphllist_delete(list->next);
    }
    free(list);
}

// File operations

llist_t* gphs_read(FILE* input_file, int max_name_len) {
    llist_t* graphs = llist_create();
    graph_t* graph_buffer = NULL;
    int c, buflen = 0;
    char buffer[max_name_len];
    vertex_t* vertex_buffer = NULL;
    status_t status = IDLE;
    while ((c = fgetc(input_file)) != EOF) {
        if (c == '\n' || c == ' ' || c == '\t') continue;
        switch (status) {
            case IDLE:
                if (c == '{') {
                    graph_buffer = gph_create();
                    status = START;
                }
                break;
            case START:
                if (c == '[')
                    status = VERTEX_READ_NAME;
                break;
            case VERTEX_READ_NAME:
                if (c == ',' || c == ']' || c == ':') {
                    // Initialise the vertex
                    vertex_buffer = vtx_create();
                    vertex_buffer->name_len = buflen;
                    vertex_buffer->name = malloc(buflen * sizeof(char));
                    strncpy(vertex_buffer->name, buffer, buflen);
                    buflen = 0;
                    // Insert the vertex into the graph's vertex tree
                    graph_buffer->vertices = vtxbstree_insert(graph_buffer->vertices, vertex_buffer);
                    graph_buffer->vertex_count++;
                    if (c == ':') status = VERTEX_READ_COLOUR;
                    else vertex_buffer = NULL;
                    if (c == ']') status = VERTEX_DONE;
                } else buffer[buflen++] = c;
                break;
            case VERTEX_READ_COLOUR:
                if (c == ',' || c == ']') {
                    char colourchars[buflen + 1];
                    colourchars[buflen] = '\0';
                    strncpy(colourchars, buffer, buflen);
                    buflen = 0;
                    int colour;
                    sscanf(colourchars, "%d", &colour);
                    vertex_buffer->colour = colour;
                    vertex_buffer = NULL;
                    if (c == ',') status = VERTEX_READ_NAME;
                    else status = VERTEX_DONE;
                } else buffer[buflen++] = c;
                break;
            case VERTEX_DONE:
                if (c == '[') status = EDGES_READ;
                else if (c == '}') status = IDLE;
                break;
            case EDGES_READ:
                if (c == '(') status = EDGE_READ_START;
                else if (c == ']') status = EDGES_DONE;
                break;
            case EDGE_READ_START:
                if (c == ',') {
                    char name[buflen+1];
                    name[buflen] = '\0';
                    strncpy(name, buffer, buflen);
                    buflen = 0;
                    vertex_buffer = vtxbstree_get(graph_buffer->vertices, name);
                    status = EDGE_READ_END;
                } else buffer[buflen++] = c;
                break;
            case EDGE_READ_END:
                if (c == ')') {
                    char name[buflen+1];
                    name[buflen] = '\0';
                    strncpy(name, buffer, buflen);
                    buflen = 0;
                    vertex_t* vertex = vtxbstree_get(graph_buffer->vertices, name);
                    vtx_create_edge(vertex, vertex_buffer);
                    status = EDGES_READ;
                } else buffer[buflen++] = c;
                break;
            case EDGES_DONE:
                if (c == '}') {
                    gphllist_insert(graphs, graph_buffer);
                    graph_buffer = NULL;
                    status = IDLE;
                }
                break;
        }
    }
    if (status != IDLE) {
        printf("Error: read_graph: Input file not complete.\n");
        exit(1);
    }
    return graphs;
}

void gphs_write(FILE* output_file, llist_t* graphs) {
    if (graphs == NULL || graphs->value == NULL)
        return;
    graph_t* graph = (graph_t*) graphs->value;
    fprintf(output_file, "{[");
    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->vertex_count);
    for (int i = 0; i < graph->vertex_count-1; i++) {
        fprintf(output_file, "%s:%d,", vertices[i]->name, vertices[i]->colour);
    }
    fprintf(output_file, "%s:%d][", vertices[graph->vertex_count-1]->name,
            vertices[graph->vertex_count-1]->colour);
    for (int i = 0; i < graph->vertex_count; i++) {
        vtx_print_edges(output_file, vertices[i]);
    }
    fprintf(output_file, "]}\n");
    free(vertices);
    gphs_write(output_file, graphs->next);
}
