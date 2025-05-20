#include <stdio.h>
#include "graph.h"

int main() {
    
    Graph* graph = createGraph(5);
    Graph* graphb = createGraph(20);

    // Add edges: from, to, weight
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 30);
    addEdge(graph, 1, 3, 40);
    addEdge(graph, 2, 3, 50);
    addEdge(graph, 3, 4, 60);

    // Print the graph
    printf("Graph structure:\n");
    printGraph(graph);
    loadGraphFromFile(graphb, "graph.txt");
    printf("Graph loaded from file:\n");
    printGraph(graphb);

    freeGraph(graph);
    freeGraph(graphb);


    return 0;
}
