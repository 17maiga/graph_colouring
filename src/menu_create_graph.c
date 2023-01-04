#include <string.h>
#include <stdlib.h>

#include "constants.h"
#include "menu_create_graph.h"
#include "menu.h"


void create_vertex_menu(graph_t* graph) {
    vertex_t* vertex = vtx_create();
    char vName[MAX_VERTEX_NAME_LEN];
    printf("Please enter the vertex name (max %d characters): ", MAX_VERTEX_NAME_LEN);
    scanf("%s", vName);

    vertex->name = malloc((strlen(vName) +1) * sizeof(char));
    strcpy(vertex->name, vName);

    vertex->name_len = strlen(vertex->name);    
    
    if (graph->order > 0) {
        print_graph_vertices(graph);
    
        int running = 1;
        char nName[MAX_VERTEX_NAME_LEN];
        
        while (running == 1) {
            printf("Did your vertex have a neighbour? [Y,N] ");
            char c;

            do {
                c = getchar();
            } while (c == '\n');

            switch (c) {
                case 'Y':
                case 'y':
                    while (c != '\n') c = getchar();
                    printf("Name of the neighbour: ");
                    scanf("%s", nName);
                    vertex_t* tmpVertex = vtxbstree_get(graph->vertices, nName);
                    if (tmpVertex == NULL) {
                        printf("This vertex does not exist\n");
                        vertex_t** vertices = vtxbstree_infix(graph->vertices, graph->order);
                        printf("Existing vertices: ");
                        for (size_t i = 0; i < graph->order; i++) {
                            printf("%s ", vertices[i]->name);
                        }
                        printf("\n");
                        free(vertices);
                    } else {
                        vtx_create_edge(vertex, tmpVertex);
                        printf("Neighbour added successfully\n");
                    }
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
        }
        
    } else {
        printf("No existing vertices..\n");
    }
    graph->vertices = vtxbstree_insert(graph->vertices, vertex);
    printf("test");
    graph->order ++;
}

void delete_vertex_menu(graph_t* graph) {
    print_graph_vertices(graph);
    printf("Please enter the vertex to delete: ");
    char vName[MAX_VERTEX_NAME_LEN + 1];
    scanf("%s", vName);
    vertex_t* vertex = vtxbstree_get(graph->vertices, vName);
    graph->vertices = vtxbstree_remove(graph->vertices, vertex);
    vtx_delete(vertex);
    graph->order--;    
}