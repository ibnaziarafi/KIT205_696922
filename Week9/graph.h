#ifndef GRAPH_H
#define GRAPH_H

typedef struct edge {
    int to_vertex;
    int weight;
} Edge;

typedef struct edgeNode {
    Edge edge;
    struct edgeNode* next;
} *EdgeNodePtr;

typedef struct edgeList {
    EdgeNodePtr head;
} EdgeList;

typedef struct graph {
    int V;
    EdgeList* edges;
} Graph;

void init_graph(Graph* g, int V);
void add_edge(Graph* g, int from, int to, int weight);
void free_graph(Graph* g);
void print_graph(Graph* g);

#endif
