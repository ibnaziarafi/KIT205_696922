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
