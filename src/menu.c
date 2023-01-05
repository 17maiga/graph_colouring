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

void display_main_menu(llist_t* graphs) {
    printf("%ld graphs loaded.\n", llist_length(graphs));
    printf("=========== Options ===========\n");
    printf("| A. Create a new graph.      |\n");
    printf("| B. Edit an existing graph.  |\n");
    printf("| C. Colour a graph.          |\n");
    printf("| D. Evaluate a coloration    |\n");
    printf("| E. Exit.                    |\n");
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
                display_main_menu(graphs);
                break;
            case 'B':
            case 'b':
                while (c != '\n') c = getchar();
                graphs_edit_menu(graphs);
                display_main_menu(graphs);
                break;
            case 'C':
            case 'c':
                while (c != '\n') c = getchar();
                color_graph_menu(graphs);
                display_main_menu(graphs);
                break;
            case 'D':
            case 'd':
                while(c != '\n') c = getchar();
                evaluate_a_graph_menu(graphs);
                display_main_menu(graphs);
                break;
            case 'E':
            case 'e':
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


void display_graph_creation_menu() {
    printf("====== Graph creation menu ====\n");
    printf("| A. Create a vertex.         |\n");
    printf("| B. Delete a vertex.         |\n");
    printf("| C. Print existing vertices. |\n");
    printf("| D. Return to main menu.     |\n");
    printf("===============================\n");
    printf("Please enter your choice: ");

}

void create_graph_menu(llist_t* graphs) {
    graph_t* graph = gph_create();
    edit_graph_menu(graph);
    gphllist_insert(graphs, graph);
}

void edit_graph_menu(graph_t* graph) {
    display_graph_creation_menu();
    int running = 1;
    
    while (running == 1) {
        char c = getchar();
        
        switch (c) {
            case 'A':
            case 'a':
                while (c != '\n') c = getchar();
                create_vertex_menu(graph);
                display_graph_creation_menu();
                break;
            case 'B':
            case 'b':
                while (c != '\n') c = getchar();
                if (graph->order != 0) {
                    delete_vertex_menu(graph);                
                } else {
                    printf("This graph haven't any vertex..\n");
                }
                display_graph_creation_menu();
                break;
            case 'C':
            case 'c':
                while (c != '\n') c = getchar();
                if (graph->order != 0) {
                    vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
                    printf("\nExisting vertices: ");
                    for (size_t i = 0; i < graph->order; i++) {
                        printf("%s ", vertices[i]->name);
                    }
                    printf("\n\n");
                    free(vertices);
                } else {
                    printf("no existing vertices\n");
                }
                display_graph_creation_menu();
                break;
            case 'D':
            case 'd':
                while (c != '\n') c = getchar();
                printf("exit\n");
                running = 0;
                break;
            case '\n':
                break;
            default:
                while (c != '\n') c = getchar();
                printf("Not a valid choice.\n");
                break;
        }
    }

}


void display_graph_edit_menu(int nb_graphs) {
    printf("=== Choose a graph to edit ===\n");
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

void graphs_edit_menu(llist_t* graphs) {
    int nb_graphs = llist_length(graphs);
    printf("%d graphs loaded.\n", nb_graphs);
    display_graph_edit_menu(nb_graphs);

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
        edit_graph_menu(graph);
    } else {
        printf("Error, this graph does not exist..\n");
        printf("No changes made.\n");
    }
}


void display_graph_evaluate_menu(int nb_graphs) {
    printf("==== Choose a graph please ====\n");
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

void evaluate_a_graph_menu(llist_t* graphs) {
    int nb_graphs = llist_length(graphs);
    printf("%d graphs loaded.\n", nb_graphs);
    display_graph_evaluate_menu(nb_graphs);

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
        int evaluation = gph_evaluation(graph);
        if (evaluation == 0) {
            printf("Graph %d is correctly coloured\n", which_graph);
        } else {
            printf("Graph %d is incorrectly coloured\n", which_graph);
        }
    } else {
        printf("Error, this graph does not exist..\n");
        printf("No changes made.\n");
    }
}