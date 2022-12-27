#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "graph.h"
#include "utils.h"

#define MAX_VERTEX_NAME_LEN 100

int main(int argc, char** argv) {
    if (argc < 2) {
        usage();
    }

    if (!strcmp("-h", argv[1])) {
        usage();
    }

    printf("%s\n", argv[1]);

    if (access(argv[1], F_OK) != 0) {
        printf("Error: File doesn't exist: %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    FILE* input_file = fopen(argv[1], "r");
    graph_t* graph = read_graph(fopen(argv[1], "r"), MAX_VERTEX_NAME_LEN);
    fclose(input_file);

    FILE* output_file = fopen("result.txt", "w");
    write_graph(output_file, graph);
    fclose(output_file);

    exit(EXIT_SUCCESS);
}
