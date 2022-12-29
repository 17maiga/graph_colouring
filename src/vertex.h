#include <stdio.h>

#include "bstree.h"
#include "llist.h"

#ifndef GRAPH_COLOUR_VERTEX_H
#define GRAPH_COLOUR_VERTEX_H

// Structure

typedef struct vertex_s {
    char* name;
    int name_len;
    int colour;
    llist_t* neighbours;
    int valence; // Number of neigbours
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
vertex_t** vtxllist_to_array(llist_t* list, int vertex_count);

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
vertex_t** vtxbstree_infix(bstree_t* tree, int vertex_count);

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
void vtx_sort_valence_desc(vertex_t** vertices, int vertex_count);

/**
 * Sorts an array of vertices in place according to their colour, in ascending
 * order. Vertices with the same colour will be arranged in ascending order of
 * their names.
 *
 * @param[in] vertices
 * @param[in] vertex_count  The number of vertices in the array.
 */
void vtx_sort_colour_asc(vertex_t** vertices, int vertex_count);

/**
 * Gets the smallest available colour for a vertex (the smallest colour not used
 * by any of the vertex's neighbours).
 *
 * @param[in]  vertex
 * @param[out] colour
 */
int vtx_get_smallest_colour(vertex_t* vertex);

#endif // GRAPH_COLOUR_VERTEX_H
