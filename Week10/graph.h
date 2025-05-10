#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int to_vertex;
    int weight;
} Edge;

typedef struct edgeNode {
    Edge edge;
    struct edgeNode* next;
} *EdgeNodePtr;

typedef struct {
    EdgeNodePtr head;
} EdgeList;

typedef struct {
    int V;
    EdgeList* edges;
} Graph;

void init_graph(Graph* g, int V);
void add_edge(Graph* g, int from, int to, int weight);
void print_graph(Graph* g);
void free_graph(Graph* g);
void calculate_pagerank(Graph* g, int iterations, double damping);

#endif
