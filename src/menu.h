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
void edit_graph_menu(graph_t* graph);

void create_graph_menu(llist_t* graphs);

void graphs_edit_menu(llist_t* graphs);

void evaluate_a_graph_menu(llist_t* graphs);

#endif // GRAPH_COLOR_UTILS_H
