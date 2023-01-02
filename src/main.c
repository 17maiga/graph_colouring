#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "graph.h"
#include "utils.h"

#define MAX_VERTEX_NAME_LEN 3

int main(int argc, char** argv) {
    if (argc < 2) {
        usage();
    }

    if (!strcmp("-h", argv[1])) {
        usage();
    }

    if (access(argv[1], F_OK) != 0) {
        printf("Error: File doesn't exist: %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Read input file
    FILE* input_file = fopen(argv[1], "r");
    llist_t* graphs = gphs_read(fopen(argv[1], "r"), MAX_VERTEX_NAME_LEN);
    fclose(input_file);

    main_menu(graphs);

    // Reduce colours
    gphs_reduce_colours(graphs);

    // Apply custom algorithm
    gphs_colour(graphs, DSATUR);

    // Write output file
    char output_file_name[strlen(argv[1]) + 8];
    strcpy(output_file_name, argv[1]);
    strcpy(output_file_name + strlen(argv[1]), ".colored");
    FILE* output_file = fopen(output_file_name, "w");
    gphs_write(output_file, graphs);
    fclose(output_file);

    exit(EXIT_SUCCESS);
}
