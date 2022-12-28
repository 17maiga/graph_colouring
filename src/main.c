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

    FILE* input_file = fopen(argv[1], "r");
    graph_t* graph = read_graph(fopen(argv[1], "r"), MAX_VERTEX_NAME_LEN);
    fclose(input_file);

    char output_file_name[strlen(argv[1]) + 8];
    strcpy(output_file_name, argv[1]);
    strcpy(output_file_name + strlen(argv[1]), ".colored");
    FILE* output_file = fopen(output_file_name, "w");
    write_graph(output_file, graph);
    fclose(output_file);

    exit(EXIT_SUCCESS);
}
