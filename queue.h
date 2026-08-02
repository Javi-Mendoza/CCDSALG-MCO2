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
Vertex *dequeue(Queue *q);
Vertex *queueHead(Queue *q);
Vertex *queueTail(Queue *q);
int queueEmpty(Queue *q);
int queueFull(Queue *q);

#endif
