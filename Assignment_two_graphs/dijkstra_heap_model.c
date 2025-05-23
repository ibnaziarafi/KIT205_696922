#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

//Min Heap node
typedef struct {
    int vertex;
    int distance;
} MinHeapNode;

typedef struct {
    int size;
    int capacity;
    int* pos;
    MinHeapNode** array;
} MinHeap;

