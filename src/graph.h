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
graph_t* create_graph();

/**
 * Frees a graph from memory.
 *
 * @param[in] graph
 */
void delete_graph(graph_t* graph);

// File operations

#define STATUS_IDLE               0
#define STATUS_START              1
#define STATUS_VERTEX_COUNT       2
#define STATUS_VERTEX_READ_NAME   3
#define STATUS_VERTEX_READ_COLOUR 4
#define STATUS_VERTEX_DONE        5
#define STATUS_EDGES_READ         6
#define STATUS_EDGE_READ_START    7
#define STATUS_EDGE_READ_END      8
#define STATUS_EDGES_DONE         9

/**
 * Reads a graph from an input file.
 *
 * @param[in] input_file
 * @param[in] max_name_len The maximum length possible for a vertex name.
 * @param[out] graph
 */
graph_t* read_graph(FILE* input_file, int max_name_len);

/**
 * Writes a graph to an output file.
 *
 * @param[in] output_file
 * @param[in] graph
 */
void write_graph(FILE* output_file, graph_t* graph);

// Processing

/**
 * Colours a graph according to a specific algorithm.
 *
 * @param[in] graph
 */
void colour_graph(graph_t* graph);

#endif // GRAPH_COLOUR_GRAPH_H
