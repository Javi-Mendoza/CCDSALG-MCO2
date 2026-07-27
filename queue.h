/*
 * queue.h
 * A manually implemented, array-based circular Queue (FIFO).
 * Used by the traversal module to implement Breadth-First Search (BFS).
 *
 * Adapted from a Token-based queue design to instead hold pointers to
 * graph vertices (Vertex*), since that's what BFS needs to enqueue/dequeue.
 * MAX_SIZE is sized generously above any plausible vertex count for this
 * assignment; the underlying array is heap-allocated by the caller
 * (see traversal.c), so a large MAX_SIZE does not risk a call-stack overflow.
 */
#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 65536

#include "graph.h"

typedef struct{

    Vertex *data[MAX_SIZE];
    int head;
    int tail;
}Queue;

void createQueue(Queue *q);
void enqueue(Queue *q, Vertex *x);
Vertex *dequeue(Queue *q);      /* returns NULL if empty */
Vertex *queueHead(Queue *q);    /* returns NULL if empty */
Vertex *queueTail(Queue *q);    /* returns NULL if empty */
int queueEmpty(Queue *q);
int queueFull(Queue *q);

#endif
