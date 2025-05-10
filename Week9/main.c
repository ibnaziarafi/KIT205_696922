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
    int from, to, weight;

    fscanf(file, "%d", &G.V);
    init_graph(&G, G.V);

    while (fscanf(file, "%d,%d,%d", &from, &to, &weight) == 3) {
        add_edge(&G, from, to, weight);
    }

    fclose(file);

    print_graph(&G);

    free_graph(&G);
    return 0;
}
