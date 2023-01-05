#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "menu_create_graph.h"
#include "menu_color_graph.h"

void usage() {
    printf("Usage: graph_colour [options] <filename>\nOptions:\n");
    printf("  -h            Display this help message.\n");
    // FIXME: Implement this stuff or delete it.
    printf("  -i            Use interactive mode.\n");
    printf("  -o FILENAME   Print output into FILENAME.\n");
    printf("  -s            Split output into separate files.\n");
    exit(EXIT_FAILURE);
}

void print_graph_vertices(graph_t* graph) {
    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
    printf("Existing vertices: ");
    for (size_t i = 0; i < graph->order; i++) {
        printf("%s ", vertices[i]->name);
    }
    printf("\n");
    free(vertices);
}

void display_main_menu(llist_t* graphs) {

    int graph_count = 0;
    llist_t* buffer = graphs;
    while (buffer != NULL && buffer->value != NULL) {
        graph_count++;
        buffer = buffer->next;
    }

    printf("%d graphs loaded.\n", graph_count);
    printf("=========== Options ===========\n");
    printf("| A. Create a new graph.      |\n");
    printf("| B. Edit an existing graph.  |\n");
    printf("| C. Colour a graph.          |\n");
    printf("| D. Exit.                    |\n");
    printf("===============================\n");
}

void display_graph_creation_menu() {
    printf("====== Graph creation menu ====\n");
    printf("| A. Create a vertex.         |\n");
    printf("| B. Delete a vertex.         |\n");
    printf("| C. Print existing vertices. |\n");
    printf("| D. Return to main menu.     |\n");
    printf("===============================\n");
}

void display_graph_coloration_menu() {
    printf("==== Graph coloration menu ====\n");
    printf("| A. Color only one graph.    |\n");
    printf("| B. Color all graphs.        |\n");
    printf("| C. Return to main menu.     |\n");
    printf("===============================\n");
}

void display_graph_coloration_algo_menu() {
    printf("========== algorithm ==========\n");
    printf("| A. DSATUR                   |\n");
    printf("| B. WELSH POWELL             |\n");
    printf("| C. CUSTOM                   |\n");
    printf("===============================\n");
}

int main_menu(llist_t* graphs) {

    int res = 0;

    display_main_menu(graphs);
    
    int running = 1;
    while (running == 1) {
        printf("Please enter your choice: ");
        char c = getchar();
        switch (c) {
            case 'A':
            case 'a':
                while (c != '\n') c = getchar();
                create_graph_menu(graphs);
                break;
            case 'B':
            case 'b':
                while (c != '\n') c = getchar();
                printf("BBB\n");
                break;
            case 'C':
            case 'c':
                while (c != '\n') c = getchar();
                color_graph_menu(graphs);
                break;
            case 'D':
            case 'd':
                while (c != '\n') c = getchar();
                printf("Would you like to save your modifications? [Y,N] \n");
                char c;

                do {
                    c = getchar();
                } while (c == '\n');
                switch (c) {
                    case 'Y':
                    case 'y':
                        while (c != '\n') c = getchar();
                        res = 1;
                        break;
                    case 'N':
                    case 'n':
                        while (c != '\n') c = getchar();
                        running = 0;
                        break;
                    default:
                        while (c != '\n') c = getchar();
                        printf("Invalid choice\n");
                        break;
                }
                running = 0;
                break;
            default:
                while (c != '\n') c = getchar();
                printf("Not a valid choice.");
                break;
        }
    }

    return res;
}

void create_graph_menu(llist_t* graphs) {
    display_graph_creation_menu();
    graph_t* graph = gph_create();
    int running = 1;
    int menuBack = 0;
    
    while (running == 1) {
        if (menuBack == 0) {
            printf("Please enter your choice: ");
        }
        char c = getchar();
        
        switch (c) {
            case 'A':
            case 'a':
                while (c != '\n') c = getchar();
                menuBack = 0;
                create_vertex_menu(graph);
                display_graph_creation_menu();
                break;
            case 'B':
            case 'b':
                while (c != '\n') c = getchar();
                menuBack = 0;
                delete_vertex_menu(graph);
                display_graph_creation_menu();
                break;
            case 'C':
            case 'c':
                while (c != '\n') c = getchar();
                printf("CCC\n");
                break;
            case 'D':
            case 'd':
                while (c != '\n') c = getchar();
                printf("exit\n");
                running = 0;
                break;
            case '\n':
                menuBack = 1;
                break;
            default:
                while (c != '\n') c = getchar();
                printf("Not a valid choice.\n");
                break;
        }
    }

    gphllist_insert(graphs, graph);
    display_main_menu(graphs);
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
                algorithm_t algorithm = chose_alorithm_menu();
                display_graph_coloration_menu();
                break;
            case 'C':
            case 'c':
                while (c != '\n') c = getchar();
                display_main_menu(graphs);
                running = 0;
                break;
        }
    }
}
