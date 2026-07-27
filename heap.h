/*
 * heap.h
 * A manually implemented binary MIN-heap (array-based), used as a
 * priority queue for Prim's Algorithm (MST) and Dijkstra's Algorithm
 * (shortest path).
 *
 * Every item pushed onto the heap comes with a plain integer priority.
 * The smallest priority number always comes out first with heapPop.
 * (For Prim's, priority is the edge weight. For Dijkstra's, priority
 * is the current known distance.)
 */
#ifndef HEAP_H
#define HEAP_H

#define HEAP_MAX_SIZE 65536

typedef struct {
    void *item;
    int priority;
} HeapEntry;

typedef struct {
    HeapEntry data[HEAP_MAX_SIZE];
    int size;
} Heap;

void createHeap(Heap *h);
void heapPush(Heap *h, void *item, int priority);
void *heapPop(Heap *h); /* removes and returns the item with the smallest priority, NULL if empty */
int heapIsEmpty(Heap *h);

#endif /* HEAP_H */
