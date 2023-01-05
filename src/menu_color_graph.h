#include "llist.h"
#include "graph.h"

#ifndef GRAPH_COLOR_MENU_COLOR_GRAPH_H
#define GRAPH_COLOR_MENU_COLOR_GRAPH_H

/**
 * Choose a graph to color
 * @param[in] graph
 */
void color_one_graph_menu(llist_t* graphs);

/**
 * @brief Color a single graph
 * 
 * @param graphs 
 */
void color_graph_menu(llist_t* graphs);

/**
 * Color every loaded graphs
 * @param[in] graph
 */
algorithm_t choose_alorithm_menu();


#endif /* GRAPH_COLOR_MENU_COLOR_GRAPH_H */
