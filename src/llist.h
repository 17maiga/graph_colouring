#include <stdio.h>

#ifndef GRAPH_COLOUR_LLIST_H
#define GRAPH_COLOUR_LLIST_H

typedef struct llist_s {
    void* value;
    struct llist_s* next;
} llist_t;

/**
 * Creates an empty linked list.
 *
 * @param[out] list
 */
llist_t* llist_create();

/**
 * Frees a linked list from memory.
 * Assumes the list's value does not need to be freed recursively. If a list is
 * used with a value that does, this function needs to be reimplemented for the
 * value's data type (see gphllist_delete).
 *
 * @param[in] list
 */
void llist_delete(llist_t* list);


size_t gphllist_count(llist_t* list);


#endif // GRAPH_COLOUR_LLIST_H
