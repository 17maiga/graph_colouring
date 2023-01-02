#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void usage() {
    printf("Usage: graph_colour [options] <filename>\nOptions:\n");
    printf("  -h            Display this help message.\n");
    // FIXME: Implement this stuff or delete it.
    printf("  -i            Use interactive mode.\n");
    printf("  -o FILENAME   Print output into FILENAME.\n");
    printf("  -s            Split output into separate files.\n");
    exit(EXIT_FAILURE);
}

void main_menu(llist_t* graphs) {
    int graph_count = 0; llist_t* buffer = graphs;
    while (buffer != NULL && buffer->value != NULL) {
        graph_count++;
        buffer = buffer->next;
    }

    printf("%d graphs loaded.\n", graph_count);
    printf("Options:\n");
    printf("A. Create a new graph.\n");
    printf("B. Edit an existing graph.\n");
    printf("C. Colour a graph.\n");
    printf("D. Exit.\n");
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
                printf("CCC\n");
                break;
            case 'D':
            case 'd':
                while (c != '\n') c = getchar();
                printf("DDD\n");
                running = 0;
                break;
            default:
                while (c != '\n') c = getchar();
                printf("Not a valid choice.");
                break;
        }
    }
}

void create_graph_menu(llist_t* graphs) {
    printf("========================================\nGraph creation menu\n");
    printf("Options:\n");
    printf("A. Create a vertex.\n");
    printf("B. Delete a vertex.\n");
    printf("C. Print existing vertices.\n");
    printf("D. Save and return to main menu.\n");
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
                printf("CCC\n");
                break;
            case 'D':
            case 'd':
                while (c != '\n') c = getchar();
                printf("DDD\n");
                running = 0;
                break;
            default:
                while (c != '\n') c = getchar();
                printf("Not a valid choice.");
                break;
        }
    }
}
