#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "graph.h"
#include "menu.h"
#include "constants.h"

int main(int argc, char** argv) {

    char outputFilename[MAX_LENGTH_OUTPUT_FILENAME];
    int isSetOutputFilename = 0;
    int haveMenu = 0;
    int haveToSplit = 0;
    int opt;

    while ((opt = getopt(argc, argv, ":o:sih")) != -1) {
        switch (opt) {
            case 'h':
                usage();
                break;
            case 'i':
                haveMenu = 1;
                break;
            case 's': 
                haveToSplit = 1;
                break;
            case 'o':
                strcpy(outputFilename, optarg);
                isSetOutputFilename = 1;
                break;
            case '?':
                printf("Error: Unknown option: %c\n", optopt);
                usage();
                break;
        }
    }    

    // Read input file
    FILE* input_file = fopen(argv[argc -1], "r");
    if (input_file == NULL) {
        printf("no such file : %s", argv[argc -1]);
        exit(EXIT_FAILURE);
    }
    
    llist_t* graphs = gphs_read(input_file, MAX_VERTEX_NAME_LEN);
    fclose(input_file);

    int save = 1;
    if (haveMenu == 1) {
        save = main_menu(graphs);
    } else {
        gphs_reduce_colours(graphs);
        
        // Apply custom algorithm
        gphs_colour(graphs, DSATUR);
    }

    if (isSetOutputFilename == 0) {
        strcpy(outputFilename, argv[argc -1]);
        strcpy(outputFilename + strlen(argv[argc -1]), ".colored");
    }

    if (save) {

        if (haveToSplit == 0)
        {
            // Write output file
            FILE* output_file = fopen(outputFilename, "w");    

            gphs_write(output_file, graphs);
            fclose(output_file);
        } else {
            int i = 0;
            int fileNameLength = strlen(outputFilename);
            while (graphs != NULL && graphs->value != NULL) {
                char tmp[10];
                sprintf(tmp, "%d", i+1);
                strcpy(outputFilename + fileNameLength, tmp);
                printf("%s\n", outputFilename);
                // Write output file
                FILE* output_file = fopen(outputFilename, "w");
                gph_write(output_file, (graph_t*) graphs->value);
                fclose(output_file);
                i++;
                graphs = graphs->next;
            }
        }
    }

    free(graphs);
    exit(EXIT_SUCCESS);
}
