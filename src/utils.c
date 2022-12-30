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
