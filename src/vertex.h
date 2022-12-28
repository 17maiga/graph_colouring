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
    int neighbours_len;
} vertex_t;

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

// Linked list interaction

/**
 * Inserts a vertex into a vertex linked list.
 * Ignores all duplicates.
 *
 * @param[in] list
 * @param[in] vertex
 * @param[out] updated_list
 */
llist_t* vtxllist_insert(llist_t* list, vertex_t* vertex);

/**
 * Gets a vertex from a vertex linked list, based on the vertex name.
 *
 * @param[in] list
 * @param[in] name
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

// Tree interaction

/**
 * Inserts a vertex into a vertex tree, based on the vertex name.
 * Ignores all duplicates.
 *
 * @param[in] tree
 * @param[in] vertex
 * @param[out] updated_tree
 */
bstree_t* vtxbstree_insert(bstree_t* tree, vertex_t* vertex);

/**
 * Gets a vertex from a vertex tree, based on the vertex name.
 *
 * @param[in] tree
 * @param[in] name
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
 * @param[in] tree
 * @param[in] vertex_count The number of vertices in the tree.
 * @param[out] vertices An array of pointers to the tree's vertices.
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
 * @param[in] start The edge's starting vertex
 * @param[in] end The edge's ending vertex
 */
void vtx_create_edge(vertex_t* start, vertex_t* end);

/**
 * Sorts an array of vertices according to their neighbour count, in descending
 * order.
 *
 * @param[in] vertices
 * @param[in] vertex_count The number of vertices in the array.
 * @param[out] sorted_vertices
 */
vertex_t** vtx_sort_neighbours_len(vertex_t** vertices, int vertex_count);

#endif // GRAPH_COLOUR_VERTEX_H
