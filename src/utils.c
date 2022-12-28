#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void usage() {
    printf("Usage: graph_colour [options] <filename>\nOptions:\n");
    printf("  -h\t\tDisplay this help message.\n");
    // FIXME: Implement this stuff or delete it.
    printf("  -o FILENAME\tPrint output into FILENAME.\n");
    printf("  -s\t\tSplit output into separate files (one per graph).\n");
    exit(EXIT_FAILURE);
}
