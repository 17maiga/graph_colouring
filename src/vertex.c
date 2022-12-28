#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertex.h"

// Linked list interaction

llist_t* vtxllist_insert(llist_t* list, vertex_t* vertex) {
    if (list == NULL)
        list = llist_create();
    if (list->value == NULL)
        list->value = vertex;
    else if (strcmp(vertex->name, ((vertex_t*) list->value)->name) != 0)
        list->next = vtxllist_insert(list->next, vertex);
    return list;
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

// Structure

vertex_t* vtx_create() {
    vertex_t* vertex = malloc(sizeof(vertex_t));
    vertex->name = NULL;
    vertex->name_len = 0;
    vertex->colour = 0;
    vertex->neighbours = llist_create();
    vertex->neighbours_len = 0;
    return vertex;
}

void vtx_delete(vertex_t* vertex) {
    free(vertex->name);
    vtxllist_delete(vertex->neighbours);
    free(vertex);
}

// Tree interaction

bstree_t* vtxbstree_insert(bstree_t* tree, vertex_t* vertex) {
    if (tree == NULL)
        tree = bstree_create();

    if (tree->value == NULL)
        tree->value = vertex;
    else if (strcmp(vertex->name, ((vertex_t*) tree->value)->name) < 0)
        tree->lft = vtxbstree_insert(tree->lft, vertex);
    else if (strcmp(vertex->name, ((vertex_t*) tree->value)->name) > 0)
        tree->rgt = vtxbstree_insert(tree->rgt, vertex);

    return tree;
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
        printf("Error: Infix path did not find expected vertex count: %d\n", vertex_count);
        exit(EXIT_FAILURE);
    }
    return res;
}

// Miscelaneous

void vtx_create_edge(vertex_t* start, vertex_t* end) {
    if (strcmp(start->name, end->name) == 0)
        return;
    start->neighbours = vtxllist_insert(start->neighbours, end);
    start->neighbours_len++;
    end->neighbours = vtxllist_insert(end->neighbours, start);
    end->neighbours_len++;
}

void vtx_print_edges_rec(FILE* output_file, char* name, llist_t* edge) {
    if (edge == NULL || edge->value == NULL) return;
    if (strcmp(name, ((vertex_t*) edge->value)->name) < 0)
        fprintf(output_file, "(%s,%s)", name, ((vertex_t*) edge->value)->name);
    vtx_print_edges_rec(output_file, name, edge->next);
}

void vtx_print_edges(FILE* output_file, vertex_t* vertex) {
    vtx_print_edges_rec(output_file, vertex->name, vertex->neighbours);
}
