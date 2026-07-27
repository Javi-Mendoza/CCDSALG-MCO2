#include <stddef.h>
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
    /* If full, the push is silently ignored rather than printed:
       the spec requires minimalist output (no text besides the
       required command output), and MAX is sized well above any
       vertex count DFS could ever need (each vertex is pushed at
       most once), so this branch should never actually be hit. */
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
