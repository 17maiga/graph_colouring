#include "llist.h"
#include "graph.h"

#ifndef GRAPH_COLOR_UTILS_H
#define GRAPH_COLOR_UTILS_H


/**
 * Prints the program's help information and exits.
 */
void usage();

/**
 * Loads the program's interactive menu.
 *
 * @param[in] graphs
 */
int main_menu(llist_t* graphs);

/**
 * Loads the program's graph creation menu.
 *
 * @param[in] graphs
 */
void create_graph_menu(llist_t* graphs);

/**
 * Print all the names of a graph vertices
 * 
 * @param[in] graph
*/
void print_graph_vertices(graph_t* graph);

#endif // GRAPH_COLOR_UTILS_H
