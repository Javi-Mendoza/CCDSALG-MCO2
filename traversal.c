#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traversal.h"
#include "queue.h"
#include "stack.h"

#define MAX_NEIGHBORS 10000

void resetVisited(Graph *g)
{
    LLNode *vn = g->vertices->head;
    while (vn != NULL)
    {
        ((Vertex *)vn->data)->visited = 0;
        vn = vn->next;
    }
}

/* ---------------- BFS ---------------- */
/*
 * Standard BFS: a vertex is marked visited the moment it is enqueued
 * (not when it is dequeued). Since each vertex's edge list is kept
 * sorted ascending by neighbor name, neighbors are naturally enqueued
 * in lexicographic order, which satisfies the "go to the lexicographically
 * smaller vertex first" tie-breaking rule.
 */
void graphBFS(Graph *g, char *start)
{
    Vertex *startV = graphFindVertex(g, start);
    if (startV == NULL)
    {
        return;
    }
    resetVisited(g);

    Queue *q = (Queue *)malloc(sizeof(Queue));
    createQueue(q);
    startV->visited = 1;
    enqueue(q, startV);

    while (!queueEmpty(q))
    {
        Vertex *cur = dequeue(q);
        printf("%s\n", cur->name);

        LLNode *en = cur->edges->head;
        while (en != NULL)
        {
            Edge *e = (Edge *)en->data;
            Vertex *nb = graphFindVertex(g, e->neighbor);
            if (nb != NULL && !nb->visited)
            {
                nb->visited = 1;
                enqueue(q, nb);
            }
            en = en->next;
        }
    }
    free(q);
}

/* ---------------- DFS ---------------- */
/*
 * Iterative, stack-based DFS. A vertex is marked visited the moment it is
 * PUSHED onto the stack (not when popped). To make the LIFO stack pop
 * neighbors in ascending (lexicographic) order, neighbors are pushed in
 * descending order, so the alphabetically smallest ends up on top.
 * This exactly reproduces the sample DFS traces in the specification.
 */
void graphDFS(Graph *g, char *start)
{
    Vertex *startV = graphFindVertex(g, start);
    if (startV == NULL)
    {
        return;
    }
    resetVisited(g);

    Stack *s = (Stack *)malloc(sizeof(Stack));
    createStack(s);
    startV->visited = 1;
    push(s, startV);

    while (!stackEmpty(s))
    {
        Vertex *cur = pop(s);
        printf("%s\n", cur->name);

        /* Collect this vertex's unvisited neighbors (already in
           ascending order) into a plain array, so we can push them
           back onto the stack in descending order afterward. */
        Vertex *toPush[MAX_NEIGHBORS];
        int n = 0;

        LLNode *en = cur->edges->head;
        while (en != NULL)
        {
            Edge *e = (Edge *)en->data;
            Vertex *nb = graphFindVertex(g, e->neighbor);
            if (nb != NULL && !nb->visited)
            {
                nb->visited = 1; /* mark visited at push time to avoid duplicates */
                if (n < MAX_NEIGHBORS)
                {
                    toPush[n] = nb;
                    n++;
                }
            }
            en = en->next;
        }

        int i;
        for (i = n - 1; i >= 0; i--)
        {
            push(s, toPush[i]);
        }
    }
    free(s);
}

/* ---------------- Path Check ---------------- */
int graphPathCheck(Graph *g, char *name1, char *name2)
{
    Vertex *v1 = graphFindVertex(g, name1);
    Vertex *v2 = graphFindVertex(g, name2);
    if (v1 == NULL || v2 == NULL)
    {
        return 0;
    }
    if (strcmp(name1, name2) == 0)
    {
        return 1;
    }

    resetVisited(g);
    Queue *q = (Queue *)malloc(sizeof(Queue));
    createQueue(q);
    v1->visited = 1;
    enqueue(q, v1);

    int found = 0;
    while (!queueEmpty(q) && !found)
    {
        Vertex *cur = dequeue(q);
        LLNode *en = cur->edges->head;
        while (en != NULL)
        {
            Edge *e = (Edge *)en->data;
            Vertex *nb = graphFindVertex(g, e->neighbor);
            if (nb != NULL && !nb->visited)
            {
                if (strcmp(nb->name, name2) == 0)
                {
                    found = 1;
                    break;
                }
                nb->visited = 1;
                enqueue(q, nb);
            }
            en = en->next;
        }
    }
    free(q);
    return found;
}
