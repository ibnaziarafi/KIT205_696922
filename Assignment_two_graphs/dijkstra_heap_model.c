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


int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}


MinHeapNode* extractMin(MinHeap* heap) {
    if (isEmpty(heap)) return NULL;

    MinHeapNode* root = heap->array[0];
    MinHeapNode* lastNode = heap->array[--heap->size];

    heap->array[0] = lastNode;
    heap->pos[root->vertex] = heap->size;
    heap->pos[lastNode->vertex] = 0;

    minHeapify(heap, 0);
    return root;
}

void decreaseKey(MinHeap* heap, int v, int dist) {
    int i = heap->pos[v];
    heap->array[i]->distance = dist;

    while (i && heap->array[i]->distance < heap->array[(i - 1) / 2]->distance) {
        heap->pos[heap->array[i]->vertex] = (i - 1) / 2;
        heap->pos[heap->array[(i - 1) / 2]->vertex] = i;
        swapMinHeapNode(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap* heap, int v) {
    return heap->pos[v] < heap->size;
}


void printHeapPath(int* parent, int v) {
    if (parent[v] == -1) {
        printf("%d", v);
        return;
    }
    printHeapPath(parent, parent[v]);
    printf(" -> %d", v);
}

void displayHeapResult(int* parent, int start, int end, int dist) {
    printf("Dijkstra (Heap): Shortest path from %d to %d: [", start, end);
    if (dist == INT_MAX) {
        printf("No path found");
    }
    else {
        printHeapPath(parent, end);
        printf("] (Distance: %d)", dist);
    }
    printf("\n");
}

//Dijkstra using min-heap
void dijkstra_heap(Graph* graph, int start, int end) {
    int V = graph->V;
    int* dist = malloc(V * sizeof(int));
    int* parent = malloc(V * sizeof(int));

    MinHeap* heap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INT_MAX;
        parent[v] = -1;
        heap->array[v] = newMinHeapNode(v, dist[v]);
        heap->pos[v] = v;
    }

    dist[start] = 0;
    decreaseKey(heap, start, dist[start]);
    heap->size = V;

    while (!isEmpty(heap)) {
        MinHeapNode* minNode = extractMin(heap);
        int u = minNode->vertex;

        EdgeNodePtr current = graph->edges[u].head;
        while (current != NULL) {
            int v = current->edge.to_vertex;
            int weight = current->edge.weight;

            if (isInMinHeap(heap, v) && dist[u] != INT_MAX &&
                dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                decreaseKey(heap, v, dist[v]);
            }
            current = current->next;
        }
        free(minNode);
    }

    displayHeapResult(parent, start, end, dist[end]);

    free(dist);
    free(parent);
    free(heap->pos);
    free(heap->array);
    free(heap);
}