#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create() {
    LL *l = (LL *) malloc(sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    return l;
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = l->head;
    l->head = n;
    return true;
}

item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *n = l->head;
    while (n != NULL) {
        if (cmp(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

void list_destroy(LL **l) {
    Node *current = (*l)->head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(*l);
    *l = NULL;
}
void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *current = l->head;
    Node *prev = NULL;
    while (current != NULL) {
        if (cmp(&current->data, i)) {
            if (prev == NULL) {
                l->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
