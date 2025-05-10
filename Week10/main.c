#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    FILE* file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    Graph G;
    int from, to;

    fscanf(file, "%d", &G.V);
    init_graph(&G, G.V);

    while (fscanf(file, "%d,%d", &from, &to) == 2) {
        add_edge(&G, from, to, 1);  
    }

    fclose(file);

    print_graph(&G); 
    calculate_pagerank(&G, 20, 0.85);

    free_graph(&G);
    return 0;
}
