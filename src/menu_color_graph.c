#include "menu_color_graph.h"

void color_one_graph_menu(llist_t* graphs) {

    int graph_count = 0;
    llist_t* buffer = graphs;
    while (buffer != NULL && buffer->value != NULL) {
        graph_count++;
        buffer = buffer->next;
        // printf("%s", ((graph_t*) graphs->value));
    }
    printf("%d graphs loaded.\n", graph_count);
}

algorithm_t chose_alorithm_menu() {
    display_graph_coloration_algo_menu();
    algorithm_t algorithm;
    printf("Chose an algorithm: ");
    char c = getchar();
    switch (c) {
        case 'A':
        case 'a':
            while (c != '\n') c = getchar();
            algorithm = DSATUR;
            return algorithm;
            break;
        case 'B':
        case 'b':
            while (c != '\n') c = getchar();
            algorithm = WELSH_POWELL;
            return algorithm;
            break;
        case 'C':
        case 'c':
            while (c != '\n') c = getchar();
            algorithm = CUSTOM;
            return algorithm;
            break;
        default:
            printf("There is a mistake...");
    }
    return 0;

}