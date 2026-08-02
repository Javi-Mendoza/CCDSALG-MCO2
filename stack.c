#include <stdlib.h>
#include "stack.h"

void createStack(Stack *S)
{
    S->top = 0;
}

int stackEmpty(Stack *S)
{
    int returnValue = 0;

    if (S->top == 0)
    {
        returnValue = 1;
    }

    return returnValue;
}

int stackFull(Stack *S)
{
    int returnValue = 0;

    if (S->top == MAX)
    {
        returnValue = 1;
    }

    return returnValue;
}

void push(Stack *S, Vertex *x)
{
    if (!stackFull(S))
    {
        S->data[S->top] = x;
        S->top++;
    }
}

Vertex *pop(Stack *S)
{
    Vertex *returnVertex = NULL;

    if (!stackEmpty(S))
    {
        S->top--;
        returnVertex = S->data[S->top];
    }

    return returnVertex;
}

Vertex *top(Stack *S)
{
    Vertex *returnVertex = NULL;

    if (!stackEmpty(S))
    {
        returnVertex = S->data[S->top - 1];
    }

    return returnVertex;
}
