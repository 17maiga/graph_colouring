#include <stdlib.h>

#include "llist.h"

llist_t* llist_create() {
    llist_t* res = malloc(sizeof(llist_t));
    res->value = NULL;
    res->next = NULL;
    return res;
}

void llist_delete(llist_t* list) {
    if (list != NULL) {
        // Assumes the list's value does not need to be freed recursively. If a
        // list is used with a value that does, this function needs to be
        // reimplemented for the value's data type (see gphllist_delete).
        free(list->value);
        llist_delete(list->next);
    }
    free(list);
}

size_t llist_length(llist_t* list) {
    llist_t* buffer = list;
    int size = 0;
    while (buffer != NULL && buffer->value != NULL){
        size ++;
        buffer = buffer->next;
    }

    return size;
}
