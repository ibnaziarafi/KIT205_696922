#include <stdio.h>
#include <time.h>
#include "graph.h"

int main() {
    
    Graph* graph = createGraph(5);
    Graph* graphb = createGraph(4000);
    Graph* graphc = createGraph(60);
    Graph* graphd = createGraph(1174);
    //initial testing stuff
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 30);
    addEdge(graph, 1, 3, 40);
    addEdge(graph, 2, 3, 50);
    addEdge(graph, 3, 4, 60);


    printf("Graph structure:\n");
    printGraph(graph);
    dijkstra(graph, 0, 3);
    dijkstra_heap(graph, 0, 3);
    //graph loading from external files
    loadGraphFromFile(graphb, "graph.txt");
    loadGraphFromFile(graphc, "graph_sec.txt");
    loadGraphFromFile(graphd, "graph_euroroad.txt");
    //graph testing using Dijkstra naive model 

    //Test phase 1
    clock_t startDN1 = clock();
    printf("Running Dijkstra:\n");
    dijkstra(graphb, 1, 3999);
    clock_t endDN1 = clock();
    double durationDN1 = (double)(endDN1 - startDN1) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN1);
    //Test phase 2
    clock_t startDN2 = clock();
    printf("Running Dijkstra:\n");
    dijkstra(graphc, 0, 12);
    clock_t endDN2 = clock();
    double durationDN2 = (double)(endDN2 - startDN2) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN2);

    //Test phase 3
    clock_t startDN3 = clock();
    printf("Running Dijkstra:\n");
    dijkstra(graphc, 27, 59);
    clock_t endDN3 = clock();
    double durationDN3 = (double)(endDN3 - startDN3) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN3);

    //Test phase 4
    clock_t startDN4 = clock();
    printf("Running Dijkstra:\n");
    dijkstra(graphd, 6, 1138);
    clock_t endDN4 = clock();
    double durationDN4 = (double)(endDN4 - startDN4) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN4);

    //graph testing using Dijkstra naive model 
    
    //Test phase 3
    //clock_t startDN3 = clock();
    //printf("Running Dijkstra:\n");
    ///*dijkstra(graphb, 1, 1999);
    //dijkstra(graphc, 0, 12);
    //dijkstra(graphc, 27, 59);*/
    //dijkstra_heap(graphd, 6, 1138);
    //clock_t endDN3 = clock();
    //double durationDN3 = (double)(endDN3 - startDN3) / CLOCKS_PER_SEC;
    //printf("Execution time: %f seconds\n", durationDN3);
    

    freeGraph(graph);
    freeGraph(graphb);


    return 0;
}
