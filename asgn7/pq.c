#include "pq.h"

#include "node.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement ListElement;

struct ListElement {
    Node *tree;
    ListElement *next;
};

struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq == NULL) {
        return NULL;
    }
    pq->list = NULL;
    return pq;
}

void pq_free(PriorityQueue **q) {
    if (*q != NULL) {
        ListElement *current = (*q)->list;
        while (current != NULL) {
            ListElement *next = current->next;
            free(current);
            current = next;
        }
        free(*q);
        *q = NULL;
    }
}

bool pq_is_empty(PriorityQueue *q) {
    return q->list == NULL;
}

bool pq_size_is_1(PriorityQueue *q) {
    return q->list != NULL && q->list->next == NULL;
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *new_element = (ListElement *) malloc(sizeof(ListElement));
    if (new_element == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_element->tree = tree;
    new_element->next = NULL;

    if (q->list == NULL || tree->weight < q->list->tree->weight) {
        new_element->next = q->list;
        q->list = new_element;
    } else {
        ListElement *current = q->list;
        while (current->next != NULL && tree->weight >= current->next->tree->weight) {
            current = current->next;
        }
        new_element->next = current->next;
        current->next = new_element;
    }
}

Node *dequeue(PriorityQueue *q) {
    if (pq_is_empty(q)) {
        fprintf(stderr, "Error: Cannot dequeue from an empty queue\n");
        exit(EXIT_FAILURE);
    }

    Node *result = q->list->tree;
    ListElement *temp = q->list;
    q->list = q->list->next;
    free(temp);
    return result;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;
    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }
    printf("=============================================\n");
}
