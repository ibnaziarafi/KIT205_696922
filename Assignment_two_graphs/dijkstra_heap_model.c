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


MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* node = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    node->vertex = v;
    node->distance = dist;
    return node;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*));
    return heap;
}


void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}


void minHeapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size &&
        heap->array[left]->distance < heap->array[smallest]->distance)
        smallest = left;

    if (right < heap->size &&
        heap->array[right]->distance < heap->array[smallest]->distance)
        smallest = right;

    if (smallest != i) {
        MinHeapNode* smallestNode = heap->array[smallest];
        MinHeapNode* iNode = heap->array[i];

        heap->pos[smallestNode->vertex] = i;
        heap->pos[iNode->vertex] = smallest;

        swapMinHeapNode(&heap->array[smallest], &heap->array[i]);
        minHeapify(heap, smallest);
    }
}

