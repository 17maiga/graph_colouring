#include <stdio.h>

#include "vertex.h"
#include "bstree.h"

#ifndef GRAPH_COLOUR_GRAPH_H
#define GRAPH_COLOUR_GRAPH_H

typedef struct graph_s {
    bstree_t* vertices;
    int vertex_count;
} graph_t;

// Structure

/**
 * Creates an empty graph.
 *
 * @param[out] graph
 */
graph_t* gph_create();

/**
 * Frees a graph from memory.
 *
 * @param[in] graph
 */
void gph_delete(graph_t* graph);

// Linked list interaction

/**
 * Inserts a graph into a graph linked list.
 * Will insert duplicates.
 *
 * @param[in] list
 * @param[in] graph
 * @param[out] updated_list
 */
llist_t* gphllist_insert(llist_t* list, graph_t* graph);

/**
 * Gets a graph from a graph linked list, based on the index.
 * Uses 0-based indexing.
 * @param[in] list
 * @param[in] index
 * @param[out] graph
 */
graph_t* gphllist_get(llist_t* list, int index);

/**
 * Frees a graph linked list from memory.
 *
 * @param[in] list
 */
void gphllist_delete(llist_t* list);

// File interaction

typedef enum {
    IDLE,
    START,
    VERTEX_READ_NAME,
    VERTEX_READ_COLOUR,
    VERTEX_DONE,
    EDGES_READ,
    EDGE_READ_START,
    EDGE_READ_END,
    EDGES_DONE
} status_t;

/**
 * Reads any number of graphs from an input file.
 *
 * @param[in] input_file
 * @param[in] max_name_len The maximum length possible for a vertex name.
 * @param[out] graphs A linked list containing the graphs.
 */
llist_t* gphs_read(FILE* input_file, int max_name_len);

/**
 * Writes any number of graphs to an output file.
 *
 * @param[in] output_file
 * @param[in] graphs A linked list containing the graphs.
 */
void gphs_write(FILE* output_file, llist_t* graph);

// Processing

typedef enum {
    CUSTOM,
} algorithm_t;

/**
 * Colours a graph according to a specific algorithm.
 *
 * @param[in] graph
 * @param[in] algorithm
 * @param[out] updated_graph
 */
graph_t* gph_colour(graph_t* graph, algorithm_t algorithm);

#endif // GRAPH_COLOUR_GRAPH_H
