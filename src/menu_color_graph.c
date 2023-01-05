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

void display_graph_coloration_algo_menu() {
    printf("========== algorithm ==========\n");
    printf("| A. DSATUR                   |\n");
    printf("| B. WELSH POWELL             |\n");
    printf("| C. CUSTOM                   |\n");
    printf("===============================\n");
}

algorithm_t choose_alorithm_menu() {
    display_graph_coloration_algo_menu();
    algorithm_t algorithm;
    int running = 1;
    while (running) {
        printf("Choose an algorithm: ");
        char c = getchar();
        switch (c) {
            case 'A':
            case 'a':
                while (c != '\n') c = getchar();
                algorithm = DSATUR;
                running = 0;
                break;
            case 'B':
            case 'b':
                while (c != '\n') c = getchar();
                algorithm = WELSH_POWELL;
                running = 0;
                break;
            case 'C':
            case 'c':
                while (c != '\n') c = getchar();
                algorithm = CUSTOM;
                running = 0;
                break;
            default:
                printf("Not an option: %c\n", c);
                break;
        }
    }
    return algorithm;
}

void display_graph_coloration_menu() {
    printf("==== Graph coloration menu ====\n");
    printf("| A. Color only one graph.    |\n");
    printf("| B. Color all graphs.        |\n");
    printf("| C. Return to main menu.     |\n");
    printf("===============================\n");
}

void color_graph_menu(llist_t* graphs) {
    display_graph_coloration_menu();

    int running = 1;
    while (running == 1) {
        printf("Please enter your choice: ");
        char c = getchar();
        switch (c) {
            case 'A':
            case 'a':
                while (c != '\n') c = getchar();
                color_one_graph_menu(graphs);
                display_graph_coloration_menu();
                break;
            case 'B':
            case 'b':
                while (c != '\n') c = getchar();
                algorithm_t algorithm = choose_alorithm_menu();
                display_graph_coloration_menu();
                break;
            case 'C':
            case 'c':
                while (c != '\n') c = getchar();
                running = 0;
                break;
        }
    }
}
