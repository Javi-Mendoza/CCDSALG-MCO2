#include <stddef.h>
#include "queue.h"

void createQueue(Queue *q)
{
    q->head = 0;
    q->tail = 0;
}

int queueEmpty(Queue *q)
{
    int boolean;
    if (q->head == q->tail)
        boolean = 1;
    else
        boolean = 0;

    return boolean;
}

int queueFull(Queue *q)
{
    int boolean;
    if (q->head == (q->tail + 1) % MAX_SIZE)
        boolean = 1;
    else
        boolean = 0;

    return boolean;
}

void enqueue(Queue *q, Vertex *x)
{
    if (!queueFull(q))
    {
        q->data[q->tail] = x;
        q->tail = (q->tail + 1) % MAX_SIZE;
    }
}

Vertex *dequeue(Queue *q)
{
    Vertex *returnVertex = NULL;

    if (!queueEmpty(q))
    {
        returnVertex = q->data[q->head];
        q->head = (q->head + 1) % MAX_SIZE;
    }

    return returnVertex;
}

Vertex *queueHead(Queue *q)
{
    Vertex *returnVertex = NULL;

    if (!queueEmpty(q))
    {
        returnVertex = q->data[q->head];
    }

    return returnVertex;
}

Vertex *queueTail(Queue *q)
{
    Vertex *returnVertex = NULL;

    if (!queueEmpty(q))
    {
        int lastElementIndex = (q->tail - 1 + MAX_SIZE) % MAX_SIZE;
        returnVertex = q->data[lastElementIndex];
    }

    return returnVertex;
}
