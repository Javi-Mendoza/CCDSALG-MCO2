#include <stddef.h>
#include "heap.h"

void createHeap(Heap *h)
{
    h->size = 0;
}

int heapIsEmpty(Heap *h)
{
    return h->size == 0;
}

void heapPush(Heap *h, void *item, int priority)
{
    if (h->size >= HEAP_MAX_SIZE)
    {
        return;
    }

    int i = h->size;
    h->data[i].item = item;
    h->data[i].priority = priority;
    h->size++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (h->data[i].priority < h->data[parent].priority)
        {
            HeapEntry temp = h->data[i];
            h->data[i] = h->data[parent];
            h->data[parent] = temp;
            i = parent;
        }
        else
        {
            break;
        }
    }
}

void *heapPop(Heap *h)
{
    if (h->size == 0)
    {
        return NULL;
    }

    void *result = h->data[0].item;

    h->size--;
    h->data[0] = h->data[h->size];

    int i = 0;
    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < h->size && h->data[left].priority < h->data[smallest].priority)
        {
            smallest = left;
        }
        if (right < h->size && h->data[right].priority < h->data[smallest].priority)
        {
            smallest = right;
        }
        if (smallest == i)
        {
            break;
        }

        HeapEntry temp = h->data[i];
        h->data[i] = h->data[smallest];
        h->data[smallest] = temp;
        i = smallest;
    }

    return result;
}
