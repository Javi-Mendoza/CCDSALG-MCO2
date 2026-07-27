/*
 * stack.h
 * A manually implemented, array-based Stack (LIFO).
 * Used by the traversal module to implement Depth-First Search (DFS).
 *
 * Adapted from a Token-based stack design to instead hold pointers to
 * graph vertices (Vertex*), since that's what DFS needs to push/pop.
 * MAX is sized generously above any plausible vertex count for this
 * assignment; the underlying array is heap-allocated by the caller
 * (see traversal.c), so a large MAX does not risk a call-stack overflow.
 */
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
Vertex *pop(Stack *S);   /* returns NULL if empty */
Vertex *top(Stack *S);   /* returns NULL if empty */
int stackEmpty(Stack *S);
int stackFull(Stack *S);

#endif
