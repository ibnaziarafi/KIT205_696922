#ifndef GRAPH_H
#define GRAPH_H

typedef struct edge Edge;
typedef struct edgeNode* EdgeNodePtr;
typedef struct edgeList EdgeList;
typedef struct graph Graph;

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

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int from, int to, int weight);
void printGraph(Graph* graph);
void loadGraphFromFile(Graph* graph, const char* filename);
void freeGraph(Graph* graph);
void dijkstra(Graph* graph, int start, int end);

#endif 
