#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertex.h"

// Linked list interaction

llist_t* vtxllist_insert_rec(llist_t* list, vertex_t* vertex) {
    if (list == NULL)
        list = llist_create();
    if (list->value == NULL)
        list->value = vertex;
    else if (strcmp(vertex->name, ((vertex_t*) list->value)->name) != 0)
        list->next = vtxllist_insert_rec(list->next, vertex);
    return list;
}

void vtxllist_insert(llist_t* list, vertex_t* vertex) {
    list = vtxllist_insert_rec(list, vertex);
}

vertex_t* vtxllist_get(llist_t* list, char* name) {
    if (list == NULL || list->value == NULL) {
        printf("Error: vtxllist_get: No such vertex: %s\n", name);
        exit(EXIT_FAILURE);
    }

    if (strcmp(name, ((vertex_t*) list->value)->name) == 0)
        return (vertex_t*) list->value;

    return vtxllist_get(list->next, name);
}

void vtxllist_delete(llist_t* list) {
    if (list != NULL) {
        // No freeing of the list's value, as it will be freed by the tree's
        // delete method.
        vtxllist_delete(list->next);
    }
    free(list);
}

vertex_t** vtxllist_to_array(llist_t* list, int vertex_count) {
    vertex_t** vertices = malloc(vertex_count * sizeof(vertex_t*));
    llist_t* buffer = list;
    int i = 0;
    while (buffer != NULL && buffer->value != NULL && i < vertex_count) {
        vertices[i] = (vertex_t*) buffer->value;
        buffer = buffer->next;
        i++;
    }
    return vertices;
}

// Structure

vertex_t* vtx_create() {
    vertex_t* vertex = malloc(sizeof(vertex_t));
    vertex->name = NULL;
    vertex->name_len = 0;
    vertex->colour = 0;
    vertex->neighbours = llist_create();
    vertex->valence = 0;
    return vertex;
}

void vtx_delete(vertex_t* vertex) {
    free(vertex->name);
    vtxllist_delete(vertex->neighbours);
    free(vertex);
}

// Tree interaction

bstree_t* vtxbstree_insert_rec(bstree_t* tree, vertex_t* vertex) {
    if (tree == NULL)
        tree = bstree_create();

    if (tree->value == NULL)
        tree->value = vertex;
    else if (strcmp(vertex->name, ((vertex_t*) tree->value)->name) < 0)
        tree->lft = vtxbstree_insert_rec(tree->lft, vertex);
    else if (strcmp(vertex->name, ((vertex_t*) tree->value)->name) > 0)
        tree->rgt = vtxbstree_insert_rec(tree->rgt, vertex);

    return tree;
}

void vtxbstree_insert(bstree_t* tree, vertex_t* vertex) {
    tree = vtxbstree_insert_rec(tree, vertex);
}

vertex_t* vtxbstree_get(bstree_t* tree, char* name) {
    if (tree == NULL || tree->value == NULL) {
        printf("Error: vtxtree_get: No such vertex: %s\n", name);
        exit(EXIT_FAILURE);
    }

    if (strcmp(name, ((vertex_t*) tree->value)->name) < 0)
        return vtxbstree_get(tree->lft, name);
    else if (strcmp(name, ((vertex_t*) tree->value)->name) > 0)
        return vtxbstree_get(tree->rgt, name);

    return (vertex_t*) tree->value;
}

void vtxbstree_delete(bstree_t* tree) {
    if (tree != NULL) {
        vtx_delete(tree->value);
        vtxbstree_delete(tree->lft);
        vtxbstree_delete(tree->rgt);
    }
    free(tree);
}

vertex_t** vtxbstree_infix_rec(bstree_t* tree, vertex_t** arr, int* size) {
    if (tree != NULL && tree->value != NULL) {
        vtxbstree_infix_rec(tree->lft, arr, size);
        arr[(*size)++] = tree->value;
        vtxbstree_infix_rec(tree->rgt, arr, size);
    }
    return arr;
}

vertex_t** vtxbstree_infix(bstree_t* tree, int vertex_count) {
    vertex_t** res = malloc(vertex_count * sizeof(vertex_t*));
    int size = 0;
    res = vtxbstree_infix_rec(tree, res, &size);
    if (size != vertex_count) {
        printf("Error: Infix path did not find expected vertex count: %d\n",
               vertex_count);
        exit(EXIT_FAILURE);
    }
    return res;
}

// File interaction

void vtx_print_edges_rec(FILE* output_file, char* name, llist_t* edge) {
    if (edge == NULL || edge->value == NULL) return;
    if (strcmp(name, ((vertex_t*) edge->value)->name) < 0)
        fprintf(output_file, "(%s,%s)", name, ((vertex_t*) edge->value)->name);
    vtx_print_edges_rec(output_file, name, edge->next);
}

void vtx_print_edges(FILE* output_file, vertex_t* vertex) {
    vtx_print_edges_rec(output_file, vertex->name, vertex->neighbours);
}

// Processing

void vtx_create_edge(vertex_t* start, vertex_t* end) {
    if (strcmp(start->name, end->name) == 0)
        return;
    vtxllist_insert(start->neighbours, end);
    start->valence++;
    vtxllist_insert(end->neighbours, start);
    end->valence++;
}

int vtx_sort_valence_desc_cmp(const void* v1, const void* v2) {
    vertex_t* vtx1 = *((vertex_t**) v1);
    vertex_t* vtx2 = *((vertex_t**) v2);
    if (vtx1->valence != vtx2->valence)
        return vtx2->valence - vtx1->valence;
    return strcmp(vtx1->name, vtx2->name);
}

void vtx_sort_valence_desc(vertex_t** vertices, int vertex_count) {
    qsort(vertices, vertex_count, sizeof(vertex_t*),
          vtx_sort_valence_desc_cmp);
}

int vtx_sort_colour_asc_cmp(const void* v1, const void* v2) {
    vertex_t* vtx1 = *((vertex_t**) v1);
    vertex_t* vtx2 = *((vertex_t**) v2);
    if (vtx1->colour != vtx2->colour)
        return vtx1->colour - vtx2->colour;
    return strcmp(vtx1->name, vtx2->name);
}

void vtx_sort_colour_asc(vertex_t** vertices, int vertex_count) {
    qsort(vertices, vertex_count, sizeof(vertex_t*),
          vtx_sort_colour_asc_cmp);
}

int vtx_get_smallest_colour(vertex_t* vertex) {
    if (vertex->valence == 0)
        return 1;
    int colour = 1, previous_colour = 1;
    vertex_t** neighbours = vtxllist_to_array(vertex->neighbours,
                                              vertex->valence);
    vtx_sort_colour_asc(neighbours, vertex->valence);
    for (int i = 0; i < vertex->valence; i++) {
        if (neighbours[i]->colour == 0)
            continue;
        if (neighbours[i]->colour - previous_colour > 1)
            // The next used colour is greater than the last seen colour by more
            // than 1, so the colour previous_colour+1 is available.
            break;
        previous_colour = neighbours[i]->colour;
        if (colour == neighbours[i]->colour)
            colour++;
    }
    if (colour == neighbours[vertex->valence-1]->colour)
        colour++;
    free(neighbours);
    return colour;
}
