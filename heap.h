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
void *heapPop(Heap *h);
int heapIsEmpty(Heap *h);

#endif /* HEAP_H */
