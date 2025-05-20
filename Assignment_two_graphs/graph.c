#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct edge {
    int to_vertex;
    int weight;
};

struct edgeNode {
    Edge edge;
    struct edgeNode* next;
};

struct edgeList {
    EdgeNodePtr head;
};

struct graph {
    int V;
    EdgeList* edges;
};

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = vertices;
    graph->edges = (EdgeList*)malloc(vertices * sizeof(EdgeList));

    for (int i = 0; i < vertices; i++) {
        graph->edges[i].head = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int from, int to, int weight) {
    EdgeNodePtr newEdgeNode = (EdgeNodePtr)malloc(sizeof(struct edgeNode));
    newEdgeNode->edge.to_vertex = to;
    newEdgeNode->edge.weight = weight;
    newEdgeNode->next = graph->edges[from].head;
    graph->edges[from].head = newEdgeNode;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        printf("Vertex %d:", i);
        EdgeNodePtr current = graph->edges[i].head;
        while (current != NULL) {
            printf(" -> %d(w=%d)", current->edge.to_vertex, current->edge.weight);
            current = current->next;
        }
        printf("\n");
    }
}

void loadGraphFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int vertices, from, to, weight;
    fscanf(file, "%d", &vertices); // First line may be number of vertices (optional)

    while (fscanf(file, "%d,%d,%d", &from, &to, &weight) == 3) {
        addEdge(graph, from, to, weight);
    }

    fclose(file);
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        EdgeNodePtr current = graph->edges[i].head;
        while (current) {
            EdgeNodePtr temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->edges);
    free(graph);
}
