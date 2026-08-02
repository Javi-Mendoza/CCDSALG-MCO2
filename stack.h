#ifndef STACK_H
#define STACK_H

#include "graph.h"

#define MAX 65536

typedef struct
{
    Vertex *data[MAX];
    int top;
} Stack;

void createStack(Stack *S);
void push(Stack *S, Vertex *x);
Vertex *pop(Stack *S);  
Vertex *top(Stack *S);
int stackEmpty(Stack *S);
int stackFull(Stack *S);

#endif
