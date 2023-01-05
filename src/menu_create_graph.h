#include "llist.h"
#include "graph.h"

#ifndef GRAPH_COLOR_MENU_CREATE_GRAPH_H
#define GRAPH_COLOR_MENU_CREATE_GRAPH_H

/**
 * Print all the names of a graph vertices
 * 
 * @param[in] graph
*/
void print_graph_vertices(graph_t* graph);

/**
 * Loads the program's vertex creation menu.
 * @param[in] graph
 */
void create_vertex_menu(graph_t* graph);

/**
 * Loads the program's vertex creation menu.
 * @param[in] graph
 */
void delete_vertex_menu(graph_t* graph);

#endif /* GRAPH_COLOR_MENU_CREATE_GRAPH_H */
