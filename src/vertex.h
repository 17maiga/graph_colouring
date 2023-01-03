#include <stdio.h>

#include "bstree.h"
#include "llist.h"

#ifndef GRAPH_COLOUR_VERTEX_H
#define GRAPH_COLOUR_VERTEX_H

// Structure

typedef int colour_t;

typedef struct vertex_s {
    char* name;
    size_t name_len;
    colour_t colour;
    llist_t* neighbours;
    size_t order; // Number of neigbours
} vertex_t;

// Linked list interaction

/**
 * Inserts a vertex into a vertex linked list.
 * Ignores all duplicates.
 *
 * @param[in]  list
 * @param[in]  vertex
 */
void vtxllist_insert(llist_t* list, vertex_t* vertex);

/**
 * Gets a vertex from a vertex linked list, based on the vertex name.
 *
 * @param[in]  list
 * @param[in]  name
 * @param[out] vertex
 */
vertex_t* vtxllist_get(llist_t* list, char* name);

/**
 * Frees a vertex linked list from memory.
 * Assumes the list's value will be freed somewhere else (in this program, by
 * the graph's vertex tree's delete method).
 *
 * @param[in] list
 */
void vtxllist_delete(llist_t* list);

/**
 * Traverses a linked list from start to end, returning an array of pointers to
 * its vertices.
 *
 * @warning This method allocates a new array into memory.
 *
 * @param[in]  list
 * @param[in]  vertex_count  The number of vertices in the list.
 * @param[out] vertices      An array of pointers to the list's vertices.
 */
vertex_t** vtxllist_to_array(llist_t* list, size_t vertex_count);

// Memory

/**
 * Creates an empty vertex.
 *
 * @param[out] vertex
 */
vertex_t* vtx_create();

/**
 * Frees a vertex from memory.
 *
 * @param[in] vertex
 */
void vtx_delete(vertex_t* vertex);

// Tree interaction

/**
 * Inserts a vertex into a vertex tree, based on the vertex name.
 * Ignores all duplicates.
 *
 * @param[in]  tree
 * @param[in]  vertex
 */
void vtxbstree_insert(bstree_t* tree, vertex_t* vertex);

/**
 * Gets a vertex from a vertex tree, based on the vertex name.
 *
 * @param[in]  tree
 * @param[in]  name
 * @param[out] vertex
 */
vertex_t* vtxbstree_get(bstree_t* tree, char* name);

/**
 * Gets the smallest vertex from a vertex tree, based on the vertex name.
 *
 * @param[in]  tree
 * @param[out] vertex
 */
vertex_t* vtxbstree_get_min(bstree_t* tree);

/**
 * Removes a vertex from a vertex tree, based on the vertex name.
 *
 * @warning This will not free the vertex, only remove it from the tree.
 *
 * @param[in] tree
 * @param[in] vertex
 */
void vtxbstree_remove(bstree_t* tree, vertex_t* name);

/**
 * Frees a vertex tree from memory.
 *
 * @param[in] tree
 */
void vtxbstree_delete(bstree_t* tree);

/**
 * Traverses the tree from left to right, returning an array of pointers to its
 * vertices.
 *
 * @warning This function allocates a new array to memory.
 *
 * @param[in]  tree
 * @param[in]  vertex_count  The number of vertices in the tree.
 * @param[out] vertices      An array of pointers to the tree's vertices.
 */
vertex_t** vtxbstree_infix(bstree_t* tree, size_t vertex_count);

// File interaction

/**
 * Prints a vertex's greater edges to a file.
 * A greater edge is any edge that goes to a vertex whose name is greater than
 * the starting node's name.
 *
 * @param[in] output_file
 * @param[in] vertex
 */
void vtx_print_edges(FILE* output_file, vertex_t* vertex);

// Processing

/**
 * Adds each vertex to the other vertex's neighbours.
 * Ignores duplicate edges.
 *
 * @param[in] start  The edge's starting vertex
 * @param[in] end    The edge's ending vertex
 */
void vtx_create_edge(vertex_t* start, vertex_t* end);

/**
 * Sorts an array of vertices in place according to their neighbour count, in
 * descending order. Vertices with the same colour will be arranges in ascending
 * order of their names.
 *
 * @param[in] vertices
 * @param[in] vertex_count  The number of vertices in the array.
 */
void vtx_sort_order_desc(vertex_t** vertices, size_t vertex_count);

/**
 * Sorts an array of vertices in place according to their colour, in ascending
 * order. Vertices with the same colour will be arranged in ascending order of
 * their names.
 *
 * @param[in] vertices
 * @param[in] vertex_count  The number of vertices in the array.
 */
void vtx_sort_colour_asc(vertex_t** vertices, size_t vertex_count);

/**
 * Gets the smallest available colour for a vertex (the smallest colour not used
 * by any of the vertex's neighbours).
 *
 * @param[in]  vertex
 * @param[out] colour
 */
colour_t vtx_get_smallest_colour(vertex_t* vertex);

/**
 * Checks if a colour is used by any of a vertex's neighbours.
 *
 * @param[in]  vertex
 * @param[in]  colour
 * @param[out] has_neighbouring_colour 1 if the colour is present, 0 otherwise
 */
int vtx_has_neighbouring_colour(vertex_t* vertex, colour_t colour);

/**
 * Returns an array of vertices containing all the uncoloured vertices in an
 * array.
 *
 * @warning This function allocates a new array in memory.
 *
 * @param[in]  vertices
 * @param[in]  vertex_count   The size of the original array.
 * @param[in]  filtered_count The size of the returned array.
 * @param[out] filtered_array
 */
vertex_t** vtx_filter_coloured(vertex_t** vertices, size_t vertex_count,
                               size_t* filtered_count);

/**
 * Returns the degree of saturation of a vertex.
 * The degree of saturation is the number of different colours used in a
 * vertex's adjacent vertices.
 *
 * @param[in]  vertex
 * @param[out] dsatur
 */
int vtx_get_dsatur(vertex_t* vertex);

/**
 * Returns the number of uncoloured vertices in a vertex's neighbours.
 *
 * @param[in]  vertex
 * @param[out] order
 */
int vtx_get_uncoloured_order(vertex_t* vertex);

/**
 * Returns the vertex with the highest degree of saturation in an array.
 * The degree of saturation is the number of different colours used in a
 * vertex's adjacent vertices.
 *
 * @param[in]  vertices
 * @param[in]  vertex_count
 * @param[out] vertex
 */
vertex_t* vtx_get_highest_dsatur(vertex_t** vertices, size_t vertex_count);

#endif // GRAPH_COLOUR_VERTEX_H
