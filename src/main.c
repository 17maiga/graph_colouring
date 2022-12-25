#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "graph.h"
#include "utils.h"

#define MAX_VERTEX_NAME_LENGTH 100

int main(int argc, char** argv)
{
    if (argc != 2) 
        usage();

    if (!strcmp("-h", argv[1])) 
        usage();

    if (!access(argv[1], F_OK))
    {
        printf("Error: File doesn't exist: %s", argv[1]);
        exit(EXIT_FAILURE);
    }
}