#ifndef GRAPH_H
#define GRAPH_H

typedef struct edge Edge;
typedef struct edgeNode* EdgeNodePtr;
typedef struct edgeList EdgeList;
typedef struct graph Graph;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int from, int to, int weight);
void loadGraphFromFile(Graph* graph, const char* filename);
void freeGraph(Graph* graph);
void printGraph(Graph* graph);

#endif 
