#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

// Memory

graph_t* gph_create() {
    graph_t* graph = malloc(sizeof(graph_t));
    graph->vertices = bstree_create();
    graph->order = 0;
    return graph;
}

void gph_delete(graph_t* graph) {
    vtxbstree_delete(graph->vertices);
    free(graph);
}

// Linked list interaction

llist_t* gphllist_insert_rec(llist_t* list, graph_t* graph) {
    if (list == NULL)
        list = llist_create();
    if (list->value == NULL)
        list->value = graph;
    else
        list->next = gphllist_insert_rec(list->next, graph);
    return list;
}

void gphllist_insert(llist_t* list, graph_t* graph) {
    list = gphllist_insert_rec(list, graph);
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

graph_t** gphllist_to_array(llist_t* list, size_t graph_count) {
    graph_t** graphs = malloc(graph_count * sizeof(graph_t*));
    llist_t* buffer = list;
    size_t i = 0;
    while (buffer != NULL && buffer->value != NULL && i < graph_count) {
        graphs[i] = (graph_t*) buffer->value;
        buffer = buffer->next;
        i++;
    }
    return graphs;
}

// File interaction

llist_t* gphs_read(FILE* input_file, size_t max_name_len) {
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
                    graph_buffer->order++;
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
                    if (vertex_buffer == NULL)
                    {
                        exit(EXIT_FAILURE);
                    }
                    
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
                    if (vertex == NULL)
                    {
                        exit(EXIT_FAILURE);
                    }
                    
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
    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
    for (size_t i = 0; i < graph->order-1; i++) {
        fprintf(output_file, "%s:%d,", vertices[i]->name, vertices[i]->colour);
    }
    fprintf(output_file, "%s:%d][", vertices[graph->order-1]->name,
            vertices[graph->order-1]->colour);
    for (size_t i = 0; i < graph->order; i++) {
        vtx_print_edges(output_file, vertices[i]);
    }
    fprintf(output_file, "]}\n");
    free(vertices);
    gphs_write(output_file, graphs->next);
}

void gph_write(FILE* output_file, graph_t* graph) {
    fprintf(output_file, "{[");
    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
    for (size_t i = 0; i < graph->order-1; i++) {
        fprintf(output_file, "%s:%d,", vertices[i]->name, vertices[i]->colour);
    }
    fprintf(output_file, "%s:%d][", vertices[graph->order-1]->name,
            vertices[graph->order-1]->colour);
    for (size_t i = 0; i < graph->order; i++) {
        vtx_print_edges(output_file, vertices[i]);
    }
    fprintf(output_file, "]}\n");
    free(vertices);
}

// Processing

int gph_has_uncoloured_vertices(graph_t* graph) {
    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
    for (size_t i = 0; i < graph->order; i++)
        if (vertices[i]->colour == 0)
            return 1;
    free(vertices);
    return 0;
}

// Personal Algorithm
// Steps:
// 1. Find the order for each vertex.
// 2. List the vertices in order of descending order.
// 3. Go down the list, colouring each vertex with the lowest possible colour
//    not used by any of the vertex's neighbours.
// Warnings:
// - Will minimize graph colours.
// - Dependent on existing colours.
void gph_colour_custom(graph_t* graph) {
    gph_reduce_colours(graph);

    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
    vtx_sort_order_desc(vertices, graph->order);

    for (size_t i = 0; i < graph->order; i++)
        vertices[i]->colour = vtx_get_smallest_colour(vertices[i]);

    free(vertices);
}

// Welsh-Powell Algorithm
// Steps:
// 1. Find the order of each vertex.
// 2. List the vertices in order of descending order.
// 3. Colour the first vertex in the list with colour 1.
// 4. Go down the list and colour every vertex not connected to the coloured
//    vertices above the same colour. Then cross out all coloured vertices in
//    the list.
// 5. Repeat the process on the uncoloured vertices with a new colour - always
//    working in descending order of order until all the vertices have been
//    coloured.
// Warnings:
// - Will minimize graph colours.
// - Dependent on existing colours.
void gph_colour_welsh_powell(graph_t* graph) {
    gph_reduce_colours(graph);
    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
    vtx_sort_order_desc(vertices, graph->order);

    // Get smallest colour not already used in graph.
    colour_t current_colour = 1;
    for (size_t i = 0; i < graph->order; i++)
        if (vertices[i]->colour >= current_colour)
            current_colour = vertices[i]->colour + 1;

    // Get uncoloured vertices.
    size_t remaining_vertices;
    vertex_t** uncoloured =
        vtx_filter_coloured(vertices, graph->order, &remaining_vertices);
    free(vertices);

    while (remaining_vertices > 0) {
        // Assign the current colour to the uncoloured vertex with the greatest
        // order.
        uncoloured[0]->colour = current_colour;

        // Assign the current colour to all uncoloured vertices not already
        // adjacent to this colour, working in descending order of order.
        for (size_t i = 0; i < remaining_vertices; i++)
            if (vtx_has_neighbouring_colour(uncoloured[i], current_colour) == 0)
                uncoloured[i]->colour = current_colour;

        // Update the uncoloured vertices.
        vertex_t** tmp = vtx_filter_coloured(uncoloured, remaining_vertices,
                                             &remaining_vertices);
        free(uncoloured);
        uncoloured = tmp;
        current_colour++;
    }

    free(uncoloured);
}

// DSatur Algorithm
// Steps:
// 1. Find the uncoloured vertex with the highest degree of saturation. In case
//    of ties, choose the vertex among these with the largest degree in the
//    subgraph induced by the uncoloured vertices.
// 2. Assign the lowest colour not being used by any of this vertex's
//    neighbours to this vertex.
// 3. If all vertices have been coloured, end. Otherwise, return to step 1.
// Warnings:
// - Will minimize graph colours.
// - Dependent on existing colours.
void gph_colour_dsatur(graph_t* graph) {
    gph_reduce_colours(graph);
    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);

    // Get uncoloured vertices;
    size_t remaining_vertices;
    vertex_t** uncoloured = vtx_filter_coloured(vertices, graph->order,
                                                &remaining_vertices);
    free(vertices);

    while (remaining_vertices > 0) {
        // Get the uncoloured vertex with the highest degree of saturation.
        vertex_t* vertex = vtx_get_highest_dsatur(uncoloured,
                                                  remaining_vertices);

        // Assign the smallest available colour possible to this vertex.
        vertex->colour = vtx_get_smallest_colour(vertex);

        // Update uncoloured vertices.
        vertex_t** tmp = vtx_filter_coloured(uncoloured, remaining_vertices,
                                             &remaining_vertices);
        free(uncoloured);
        uncoloured = tmp;
    }

    free(uncoloured);
}

void gph_colour(graph_t* graph, algorithm_t algorithm) {
    switch (algorithm) {
        case CUSTOM:
            gph_colour_custom(graph);
            break;
        case WELSH_POWELL:
            gph_colour_welsh_powell(graph);
            break;
        case DSATUR:
            gph_colour_dsatur(graph);
            break;
    }
}

void gphs_colour(llist_t* graphs, algorithm_t algorithm) {
    llist_t* buffer = graphs;
    while (buffer != NULL && buffer->value != NULL) {
        gph_colour(buffer->value, algorithm);
        buffer = buffer->next;
    }
}

void gph_reduce_colours(graph_t* graph) {
    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
    vtx_sort_colour_asc(vertices, graph->order);
    int prev_colour = 0, set_colour = 0;

    for (size_t i = 0; i < graph->order; i++) {
        if (vertices[i]->colour == 0)
            continue;
        if (vertices[i]->colour != prev_colour) {
            prev_colour = vertices[i]->colour;
            set_colour++;
        }
        vertices[i]->colour = set_colour;
    }

    free(vertices);
}

void gphs_reduce_colours(llist_t* graphs) {
    llist_t* buffer = graphs;
    while (buffer != NULL && buffer->value != NULL) {
        gph_reduce_colours(buffer->value);
        buffer = buffer->next;
    }
}
