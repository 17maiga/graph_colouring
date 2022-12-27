#include <stdlib.h>

#include "llist.h"

llist_t* create_llist() {
    llist_t* res = malloc(sizeof(llist_t));
    res->value = NULL;
    res->next = NULL;
    return res;
}

void delete_llist(llist_t* list) {
    if (list != NULL) {
        // No freeing of the node value, as it will be freed in the tree.
        delete_llist(list->next);
    }
    free(list);
}
