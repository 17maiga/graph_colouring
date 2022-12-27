#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vertex.h"

// Structure

vertex_t* create_vertex() {
    vertex_t* vertex = malloc(sizeof(vertex_t));
    vertex->name = NULL;
    vertex->name_len = 0;
    vertex->colour = 0;
    vertex->neighbours = create_llist();
    vertex->neighbours_len = 0;
    return vertex;
}

void delete_vertex(vertex_t* vertex) {
    free(vertex->name);
    delete_llist(vertex->neighbours);
    free(vertex);
}

// Linked list interaction

void vtxllist_insert(llist_t* list, vertex_t* vertex) {
    if (list == NULL) {
        list = create_llist();
        list->value = vertex;
    } else {
        if (!strcmp(vertex->name, ((vertex_t*) list->value)->name)) return;
        vtxllist_insert(list->next, vertex);
    }
}

vertex_t* vtxllist_get(llist_t* list, char* name) {
    if (list == NULL) {
        printf("Error: vtxllist_get: No such vertex: %s\n", name);
        exit(EXIT_FAILURE);
    }

    if (!strcmp(name, ((vertex_t*) list->value)->name))
        return (vertex_t*) list->value;

    return vtxllist_get(list->next, name);
}

// Tree interaction

void vtxtree_insert(bstree_t* tree, vertex_t* vertex) {
    if (tree == NULL) {
        tree = create_tree();
        tree->value = vertex;
    } else if (strcmp(vertex->name, ((vertex_t*) tree->value)->name) < 0)
        vtxtree_insert(tree->lft, vertex);
    else if (strcmp(vertex->name, ((vertex_t*) tree->value)->name) > 0)
        vtxtree_insert(tree->rgt, vertex);
}

vertex_t* vtxtree_get(bstree_t* tree, char* name) {
    if (tree == NULL) {
        printf("Error: vtxtree_get: No such vertex: %s\n", name);
        exit(EXIT_FAILURE);
    }

    if (strcmp(name, ((vertex_t*) tree->value)->name) < 0)
        return vtxtree_get(tree->lft, name);
    else if (strcmp(name, ((vertex_t*) tree->value)->name) > 0)
        return vtxtree_get(tree->rgt, name);

    return (vertex_t*) tree->value;
}

int vtxtree_infix_rec(bstree_t* tree, vertex_t** res, int index) {
    if (tree == NULL) return index;
    index = vtxtree_infix_rec(tree->lft, res, index);
    res[index++] = tree->value;
    return vtxtree_infix_rec(tree->rgt, res, index);
}

vertex_t** vtxtree_infix(bstree_t* tree, int vertex_count) {
    vertex_t** res = malloc(vertex_count * sizeof(vertex_t*)); // FIXME: Free memory when needed
    if (infix_path_recursive(tree, res, 0) != vertex_count - 1) {
        printf("Error: Infix path did not find expected vertex count: %d\n", vertex_count);
        exit(EXIT_FAILURE);
    }
    return res;
}

// Miscelaneous

void create_edge(vertex_t* start, vertex_t* end) {
    vtxllist_insert(start->neighbours, end);
    start->neighbours_len++;
    vtxllist_insert(end->neighbours, start);
    end->neighbours_len++;
}

void vtx_print_edges_rec(FILE* output_file, char* name, llist_t* edge) {
    if (edge == NULL) return;
    if (strcmp(name, ((vertex_t*) edge->value)->name) < 0)
        fprintf(output_file, "(%s,%s)", name, ((vertex_t*) edge->value)->name);
    vtx_print_edges_rec(output_file, name, edge->next);
}

void vtx_print_edges(FILE* output_file, vertex_t* vertex) {
    vtx_print_edges_rec(output_file, vertex->name, vertex->neighbours);
}
