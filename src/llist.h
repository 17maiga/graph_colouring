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
llist_t* create_llist();

/**
 * Frees a linked list from memory.
 *
 * @param[in] list
 */
void delete_llist(llist_t* list);

#endif // GRAPH_COLOUR_LLIST_H
