#include <stdio.h>
#include <time.h>
#include "graph.h"

int main() {
    
    Graph* graph = createGraph(5);
    Graph* graphb = createGraph(4000);
    Graph* graphc = createGraph(60);
    Graph* graphd = createGraph(1174);

    //graph loading from external files
    loadGraphFromFile(graphb, "graph.txt");
    loadGraphFromFile(graphc, "graph_sec.txt");
    loadGraphFromFile(graphd, "graph_euroroad.txt");
    //initial testing stuff
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 30);
    addEdge(graph, 1, 3, 40);
    addEdge(graph, 2, 3, 50);
    addEdge(graph, 3, 4, 60);


    printf("Graph structure:\n");
    printGraph(graph);
    printGraph(graphc);
    dijkstra(graph, 0, 3);
    dijkstra_heap(graph, 0, 3);

    //Naive and heap dijkstra model testing side by side
    printf("\n------------------------------------------------------\n");
    printf("Naive and heap dijkstra model testing side by side\n");

    //Test phase 1 (naive)
    clock_t startDN1 = clock();
    printf("Running Dijkstra(total vertices 4000):\n");
    dijkstra(graphb, 1, 3999);
    clock_t endDN1 = clock();
    double durationDN1 = (double)(endDN1 - startDN1) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN1);
    //Test phase 1 (min-heap)
    clock_t startDH1 = clock();
    printf("Running Dijkstra heap model(total vertices 4000):\n");
    dijkstra_heap(graphb, 1, 3999);
    clock_t endDH1 = clock();
    double durationDH1 = (double)(endDH1 - startDH1) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDH1);
    printf("\n");
    
    //Test phase 2 (naive)
    clock_t startDN2 = clock();
    printf("Running Dijkstra(total vertices 60):\n");
    dijkstra(graphc, 0, 12);
    clock_t endDN2 = clock();
    double durationDN2 = (double)(endDN2 - startDN2) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN2);
    //Test phase 2 (min-heap)
    clock_t startDH2 = clock();
    printf("Running Dijkstra heap model(total vertices 60):\n");
    dijkstra_heap(graphc, 0, 12);
    clock_t endDH2 = clock();
    double durationDH2 = (double)(endDH2 - startDH2) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDH2);
    printf("\n");
    //Test phase 3 (naive)
    clock_t startDN3 = clock();
    printf("Running Dijkstra(total vertices 60):\n");
    dijkstra(graphc, 27, 59);
    clock_t endDN3 = clock();
    double durationDN3 = (double)(endDN3 - startDN3) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN3);
    //Test phase 3 (min-heap)
    clock_t startDH3 = clock();
    printf("Running Dijkstraheap model(total vertices 60):\n");
    dijkstra_heap(graphc, 27, 59);
    clock_t endDH3 = clock();
    double durationDH3 = (double)(endDH3 - startDH3) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDH3);
    printf("\n");

    //Test phase 4 (naive)
    clock_t startDN4 = clock();
    printf("Running Dijkstra(total vertices 1174):\n");
    dijkstra(graphd, 6, 1138);
    clock_t endDN4 = clock();
    double durationDN4 = (double)(endDN4 - startDN4) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN4);
    //Test phase 4 (min-heap)
    clock_t startDH4 = clock();
    printf("Running Dijkstra heap model(total vertices 1174):\n");
    dijkstra_heap(graphd, 6, 1138);
    clock_t endDH4 = clock();
    double durationDH4 = (double)(endDH4 - startDH4) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDH4);
    printf("\n");

    //Test phase 5 (naive)
    clock_t startDN5 = clock();
    printf("Running Dijkstra(total vertices 4000):\n");
    dijkstra(graphb, 100, 3666);
    clock_t endDN5 = clock();
    double durationDN5 = (double)(endDN5 - startDN5) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDN5);
    //Test phase 5 (min-heap)
    clock_t startDH5 = clock();
    printf("Running Dijkstra heap model(total vertices 4000):\n");
    dijkstra_heap(graphb, 100, 3666);
    clock_t endDH5 = clock();
    double durationDH5 = (double)(endDH5 - startDH5) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", durationDH5);
    printf("\n");


 
    



    freeGraph(graph);
    freeGraph(graphb);
    freeGraph(graphc);
    freeGraph(graphd);


    return 0;
}
