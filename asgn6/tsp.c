#include "graph.h"
#include "path.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define START_VERTEX 0
#define OPTIONS      "do:hi:"

// Print help message
void print_help(void) {
    printf("Usage: tsp -i <input_file> [-d] [-h]\n");
    printf("Options:\n");
    printf("  -i <input_file>: Specifies the input file containing the graph data\n");
    printf("  -d: Treats all graphs as directed\n");
    printf("  -h: Prints this help message\n");
}

// Read graph from file
bool read_graph(const char *filename, Graph **g, bool directed) {
    FILE *file = fopen(filename, "r");
    if (strcmp(filename, "stdin") == 0) {
        file = stdin;
    }
    if (!file)
        return false;

    uint32_t num_vertices;
    if (fscanf(file, "%u", &num_vertices) != 1) {
        fclose(file);
        return false;
    }

    *g = graph_create(num_vertices, directed);
    char name[100];
    for (uint32_t i = 0; i <= num_vertices; i++) {
        if (fgets(name, sizeof(name), file) != NULL) {
            if (strcmp(name, "\n") != 0) {
                name[strcspn(name, "\r\n")] = 0;
                graph_add_vertex(*g, name, i - 1);
            }
        } else {
            fclose(file);
            graph_free(g);
            return false;
        }
    }

    uint32_t num_edges = 1;
    int scan = fscanf(file, "%u", &num_edges);
    if (scan != 1) {
        fclose(file);
        graph_free(g);
        return false;
    }
    for (uint32_t i = 0; i < num_edges; i++) {
        uint32_t start, end, weight;
        if (fscanf(file, "%u %u %u", &start, &end, &weight) != 3) {
            fclose(file);
            graph_free(g);
            return false;
        }
        graph_add_edge(*g, start, end, weight);
    }

    fclose(file);
    return true;
}

// Find Hamiltonian cycle using DFS
bool find_hamiltonian_cycle(Graph *g, Path *p, uint32_t start_vertex, bool directed) {
    graph_visit_vertex(g, start_vertex);
    path_add(p, start_vertex, g);
    if (path_vertices(p) == graph_vertices(g)) {
        uint32_t end_vertex;
        stack_peek(get_vertices(p), &end_vertex);
        if (graph_get_weight(g, end_vertex, START_VERTEX) > 0) {
            return true;
        }
    }

    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        if (graph_get_weight(g, start_vertex, i) > 0 && !graph_visited(g, i)) {
            if (find_hamiltonian_cycle(g, p, i, directed)) {
                return true;
            }
        }
    }

    uint32_t removed_vertex;
    stack_pop(get_vertices(p), &removed_vertex);
    graph_unvisit_vertex(g, start_vertex);
    return false;
}

int main(int argc, char *argv[]) {
    bool directed = false;
    const char *filename = "stdin";
    int opt;
    FILE *file = stdout;

    // Parse command line options
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': filename = optarg; break;
        case 'd': directed = true; break;
        case 'o': file = fopen(optarg, "w"); break;
        case 'h': print_help(); return 0;
        default: fprintf(stderr, "Usage: %s -i <input_file> [-d] [-h]\n", argv[0]); return 1;
        }
    }
    // Read graph from file
    Graph *g = NULL;
    if (filename) {
        if (!(read_graph(filename, &g, directed))) {
            fprintf(stderr, "Error: Unable to read the graph from file '%s'\n", filename);
            return 1;
        }
    } else {
        fprintf(stderr, "Error: No input file specified.\n");
        return 1;
    }

    // Find Hamiltonian cycle
    Path *p = path_create(graph_vertices(g) + 1);
    if (!find_hamiltonian_cycle(g, p, START_VERTEX, directed)) {
        printf("No path found! Alissa is lost!\n");
    } else {
        path_add(p, START_VERTEX, g);
        fprintf(file, "Alissa starts at:\n");
        path_print(p, file, g);
        fprintf(file, "Total Distance: %u\n", path_distance(p));
    }

    // Free allocated memory
    path_free(&p);
    graph_free(&g);
    fclose(file);
    return 0;
}
