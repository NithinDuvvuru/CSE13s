#include "graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct graph {
    uint32_t vertices;
    bool directed;
    bool *visited;
    char **names;
    uint32_t **weights;
};

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    if (g == NULL) {
        return NULL; // Allocation failed
    }
    g->vertices = vertices;
    g->directed = directed;
    g->visited = calloc(vertices, sizeof(bool));
    if (g->visited == NULL) {
        free(g);
        return NULL; // Allocation failed
    }
    g->names = calloc(vertices, sizeof(char *));
    if (g->names == NULL) {
        free(g->visited);
        free(g);
        return NULL; // Allocation failed
    }
    g->weights = calloc(vertices, sizeof(uint32_t *));
    if (g->weights == NULL) {
        free(g->names);
        free(g->visited);
        free(g);
        return NULL; // Allocation failed
    }
    // Allocate memory for each row in the adjacency matrix
    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(uint32_t));
        if (g->weights[i] == NULL) {
            // Free previously allocated memory
            for (uint32_t j = 0; j < i; ++j) {
                free(g->weights[j]);
            }
            free(g->weights);
            free(g->names);
            free(g->visited);
            free(g);
            return NULL; // Allocation failed
        }
    }
    return g;
}

void graph_free(Graph **gp) {
    if (gp == NULL || *gp == NULL) {
        return;
    }
    Graph *g = *gp;
    // Free allocated memory for names
    for (uint32_t i = 0; i < g->vertices; ++i) {
        free(g->names[i]);
    }
    free(g->names);
    // Free allocated memory for visited array
    free(g->visited);
    // Free allocated memory for weights matrix
    for (uint32_t i = 0; i < g->vertices; ++i) {
        free(g->weights[i]);
    }
    free(g->weights);
    // Free graph structure
    free(g);
    *gp = NULL;
}

uint32_t graph_vertices(const Graph *g) {
    if (g == NULL) {
        return 0;
    }
    return g->vertices;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (g->names[v])
        free(g->names[v]);
    g->names[v] = strdup(name);
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    if (g == NULL || v >= g->vertices) {
        return NULL;
    }
    return g->names[v];
}

char **graph_get_names(const Graph *g) {
    if (g == NULL) {
        return NULL;
    }
    return g->names;
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    if (g == NULL || start >= g->vertices || end >= g->vertices) {
        return;
    }
    g->weights[start][end] = weight;
    if (!g->directed) {
        g->weights[end][start] = weight; // If undirected, also add edge from end to start
    }
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    if (g == NULL || start >= g->vertices || end >= g->vertices) {
        return 0;
    }
    return g->weights[start][end];
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    if (g == NULL || v >= g->vertices) {
        return;
    }
    g->visited[v] = true;
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    if (g == NULL || v >= g->vertices) {
        return;
    }
    g->visited[v] = false;
}

bool graph_visited(const Graph *g, uint32_t v) {
    if (g == NULL || v >= g->vertices) {
        return false;
    }
    return g->visited[v];
}

void graph_print(const Graph *g) {
    if (g == NULL) {
        return;
    }
    printf("Vertices: %d\n", g->vertices);
    printf("Directed: %s\n", g->directed ? "true" : "false");
    printf("Visited:\n");
    for (uint32_t i = 0; i < g->vertices; ++i) {
        printf("%d: %s\n", i, g->visited[i] ? "true" : "false");
    }
    printf("Names:\n");
    for (uint32_t i = 0; i < g->vertices; ++i) {
        printf("%d: %s\n", i, g->names[i]);
    }
    printf("Weights:\n");
    for (uint32_t i = 0; i < g->vertices; ++i) {
        for (uint32_t j = 0; j < g->vertices; ++j) {
            printf("%d ", g->weights[i][j]);
        }
        printf("\n");
    }
}
