#include <stdio.h>

#include "vertex.h"
#include "bstree.h"

#ifndef GRAPH_COLOUR_GRAPH_H
#define GRAPH_COLOUR_GRAPH_H

// Structure

typedef struct graph_s {
    bstree_t* vertices;
    size_t order;
} graph_t;

// Memory

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

/**
 * Evaluate the coloration of a graph
 * 
 * @param[in] graph
 * @param[out] int
*/
int gph_evaluation(graph_t* graph);

/**
 * Reset the coloration of a graph
 * 
 * @param[in] graph
*/
void gph_reset(graph_t* graph);

// Linked list interaction

/**
 * Inserts a graph into a graph linked list.
 * Will insert duplicates.
 *
 * @param[in]  list
 * @param[in]  graph
 */
void gphllist_insert(llist_t* list, graph_t* graph);

/**
 * Gets a graph from a graph linked list, based on the index.
 * Uses 0-based indexing.
 * @param[in]  list
 * @param[in]  index
 * @param[out] graph
 */
graph_t* gphllist_get(llist_t* list, int index);

/**
 * Frees a graph linked list from memory.
 *
 * @param[in] list
 */
void gphllist_delete(llist_t* list);

/**
 * Traverses a linked list from start to end, returning an array of pointers to
 * its vertices.
 *
 * @warning This method allocates a new array into memory.
 *
 * @param[in] graphs
 * @param[in] graph_count
 * @param[out] array
 */
graph_t** gphllist_to_array(llist_t* graphs, size_t graph_count);

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
 * @param[in]  input_file
 * @param[in]  max_name_len  The maximum length possible for a vertex name.
 * @param[out] graphs        A linked list containing the graphs.
 */
llist_t* gphs_read(FILE* input_file, size_t max_name_len);

/**
 * Writes any number of graphs to an output file.
 *
 * @param[in] output_file
 * @param[in] graphs       A linked list containing the graphs.
 */
void gphs_write(FILE* output_file, llist_t* graph);

/**
 * Writes any number of graphs to an output file.
 *
 * @param[in] output_file
 * @param[in] graphs       A linked list containing the graphs.
 */
void gph_write(FILE* output_file, graph_t* graph);

// Processing

typedef enum {
    CUSTOM,
    WELSH_POWELL,
    DSATUR
} algorithm_t;

/**
 * Checks if a graph still has uncoloured vertices.
 *
 * @param[in]  graph
 * @param[out] 1 if it does, 0 otherwise.
 */
int gph_has_uncoloured_vertices(graph_t* graph);

/**
 * Colours a graph according to a specific algorithm.
 *
 * @param[in]  graph
 * @param[in]  algorithm
 * @param[out] updated_graph
 */
void gph_colour(graph_t* graph, algorithm_t algorithm);

/**
 * Colours a graph according to a specific algorithm for each graph in a graph
 * linked list.
 *
 * @param[in] graphs
 * @param[in] algorithm
 */
void gphs_colour(llist_t* graphs, algorithm_t algorithm);

/**
 * Sets a graph's colours to the smallest possible values.
 *
 * If a graph is passed in with colours [1, 3, 75], the returned graph will have
 * colours [1, 2, 3], and each vertex will be updated accordingly. Vertices with
 * no colour set (i.e. colour = 0) will be skipped.
 *
 * @param[in] graph
 */
void gph_reduce_colours(graph_t* graph);

/**
 * Sets a graph's colours to the smallest possible values for each graph in a
 * graph linked list.
 *
 * @param[in] graphs
 */
void gphs_reduce_colours(llist_t* graphs);

#endif // GRAPH_COLOUR_GRAPH_H
