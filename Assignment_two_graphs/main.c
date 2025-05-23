#include <stdio.h>
#include <time.h>
#include "graph.h"

int main() {
    
    Graph* graph = createGraph(5);
    Graph* graphb = createGraph(4000);
    Graph* graphc = createGraph(60);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 30);
    addEdge(graph, 1, 3, 40);
    addEdge(graph, 2, 3, 50);
    addEdge(graph, 3, 4, 60);


    printf("Graph structure:\n");
    printGraph(graph);
    dijkstra_heap(graph, 0, 3);
    dijkstra(graph, 0, 3);
    loadGraphFromFile(graphb, "graph.txt");
    loadGraphFromFile(graphc, "graph_sec.txt");
    
    clock_t start = clock();
    printf("Running Dijkstra:\n");
    dijkstra(graphb, 1, 1999);
    dijkstra(graphc, 0, 12);
    dijkstra(graphc, 27, 59);
    clock_t end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", duration);
    
    

    freeGraph(graph);
    freeGraph(graphb);


    return 0;
}
