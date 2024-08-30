#include "path.h"

#include "graph.h"
#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

// Function to create a new path
Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    return p;
}

Stack *get_vertices(const Path *p) {
    return p->vertices;
}

// Function to free memory allocated for the path
void path_free(Path **pp) {
    if (pp != NULL && *pp != NULL) {
        stack_free(&((*pp)->vertices));
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

// Function to find the number of vertices in a path
uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

// Function to find the distance covered by a path
uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

// Function to add vertex val from graph g to the path
void path_add(Path *p, uint32_t val, const Graph *g) {
    uint32_t prev_vertex;
    if (!stack_empty(p->vertices)) {
        stack_peek(p->vertices, &prev_vertex);
        p->total_weight += graph_get_weight(g, prev_vertex, val);
    }
    stack_push(p->vertices, val);
}

// Function to remove the most recently added vertex from the path
uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t removed_vertex;
    stack_pop(p->vertices, &removed_vertex);
    if (!stack_empty(p->vertices)) {
        uint32_t prev_vertex;
        stack_peek(p->vertices, &prev_vertex);
        p->total_weight -= graph_get_weight(g, prev_vertex, removed_vertex);
    } else {
        p->total_weight = 0;
    }
    return removed_vertex;
}

// Function to copy a path from src to dst
void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
}

// Function to print the path stored, using the vertex names from g, to the file outfile
void path_print(const Path *p, FILE *outfile, const Graph *g) {
    Stack *temp_stack = stack_create(stack_size(p->vertices));
    while (!stack_empty(p->vertices)) {
        uint32_t vertex;
        stack_pop(p->vertices, &vertex);
        stack_push(temp_stack, vertex);
    }
    while (!stack_empty(temp_stack)) {
        uint32_t vertex;
        stack_pop(temp_stack, &vertex);
        fprintf(outfile, "%s\n", graph_get_vertex_name(g, vertex));
    }
    stack_free(&temp_stack);
}
