#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void init_graph(Graph* g, int V) {
    g->V = V;
    g->edges = (EdgeList*)malloc(V * sizeof(EdgeList));
    for (int i = 0; i < V; i++) {
        g->edges[i].head = NULL;
    }
}

void add_edge(Graph* g, int from, int to, int weight) {
    EdgeNodePtr new_node = (EdgeNodePtr)malloc(sizeof(struct edgeNode));
    new_node->edge.to_vertex = to;
    new_node->edge.weight = weight;
    new_node->next = g->edges[from].head;
    g->edges[from].head = new_node;
}

void print_graph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        printf("Vertex %d:", i);
        EdgeNodePtr curr = g->edges[i].head;
        while (curr != NULL) {
            printf(" -> %d", curr->edge.to_vertex);
            curr = curr->next;
        }
        printf("\n");
    }
}

void free_graph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        EdgeNodePtr curr = g->edges[i].head;
        while (curr != NULL) {
            EdgeNodePtr temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g->edges);
}

void calculate_pagerank(Graph* g, int iterations, double damping) {
    int V = g->V;
    double* pagerank = malloc(V * sizeof(double));
    double* new_pagerank = malloc(V * sizeof(double));
    int* out_degree = calloc(V, sizeof(int));
    double* sums = calloc(V, sizeof(double));

    for (int i = 0; i < V; i++) {
        pagerank[i] = 1.0;
    }

    for (int i = 0; i < V; i++) {
        EdgeNodePtr curr = g->edges[i].head;
        while (curr != NULL) {
            out_degree[i]++;
            curr = curr->next;
        }
    }

    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < V; i++) {
            sums[i] = 0.0;
        }

        for (int from = 0; from < V; from++) {
            EdgeNodePtr curr = g->edges[from].head;
            while (curr != NULL) {
                int to = curr->edge.to_vertex;
                if (out_degree[from] > 0) {
                    sums[to] += pagerank[from] / out_degree[from];
                }
                curr = curr->next;
            }
        }

        for (int i = 0; i < V; i++) {
            new_pagerank[i] = (1.0 - damping) + damping * sums[i];
        }

        for (int i = 0; i < V; i++) {
            pagerank[i] = new_pagerank[i];
        }
    }

    printf("\nPageRank after %d iterations:\n", iterations);
    for (int i = 0; i < V; i++) {
        printf("Vertex %d: %.5f\n", i, pagerank[i]);
    }

    free(pagerank);
    free(new_pagerank);
    free(out_degree);
    free(sums);
}
