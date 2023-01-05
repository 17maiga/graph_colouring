#include "menu_color_graph.h"

void display_graph_coloration_algo_menu() {
    printf("========== algorithm ==========\n");
    printf("| A. DSATUR                   |\n");
    printf("| B. WELSH POWELL             |\n");
    printf("| C. CUSTOM                   |\n");
    printf("===============================\n");
}

algorithm_t choose_algorithm_menu() {
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

void display_graphs_coloration_menu() {
    printf("==== Graph coloration menu ====\n");
    printf("| A. Color only one graph.    |\n");
    printf("| B. Color all graphs.        |\n");
    printf("| C. Return to main menu.     |\n");
    printf("===============================\n");
}

void color_graph_menu(llist_t* graphs) {
    display_graphs_coloration_menu();

    int running = 1;
    while (running == 1) {
        printf("Please enter your choice: ");
        char c = getchar();
        switch (c) {
            case 'A':
            case 'a':
                while (c != '\n') c = getchar();
                color_one_graph_menu(graphs);
                display_graphs_coloration_menu();
                break;
            case 'B':
            case 'b':
                while (c != '\n') c = getchar();
                algorithm_t algorithm = choose_algorithm_menu();
                gphs_colour(graphs, algorithm);
                display_graphs_coloration_menu();
                break;
            case 'C':
            case 'c':
                while (c != '\n') c = getchar();
                running = 0;
                break;
        }
    }
}

void display_graph_coloration_menu(int nb_graphs) {
    printf("=== Choose a graph to color ===\n");
    for (int i = 1; i <= nb_graphs; i++) {
        if (nb_graphs < 10) {
            printf("| %d.                          |\n", i);
        } else if (nb_graphs < 100) {
            printf("| %d.                         |\n", i);
        } else {
            printf("| %d.                        |\n", i);
        }        
    }
    printf("===============================\n");
}

void color_one_graph_menu(llist_t* graphs) {
    int nb_graphs = llist_length(graphs);
    printf("%d graphs loaded.\n", nb_graphs);
    display_graph_coloration_menu(nb_graphs);

    int which_graph;
    char buffer[3];
    int c, bufflen = 0;
    printf("Choose the graph: ");
    while ((c = getchar()) != '\n') {
        if ('0' <= c && c <= '9') {
            buffer[bufflen++] = c;
        }
    }
    sscanf(buffer, "%d", &which_graph);
    if (which_graph <= nb_graphs) {
        graph_t* graph = gphllist_get(graphs, which_graph -1);
        algorithm_t algorithm = choose_algorithm_menu();
        gph_colour(graph, algorithm);
    } else {
        printf("Error, this graph does not exist..\n");
        printf("No changes made.\n");
    }
}