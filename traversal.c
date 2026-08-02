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

        Vertex *toPush[MAX_NEIGHBORS];
        int n = 0;

        LLNode *en = cur->edges->head;
        while (en != NULL)
        {
            Edge *e = (Edge *)en->data;
            Vertex *nb = graphFindVertex(g, e->neighbor);
            if (nb != NULL && !nb->visited)
            {
                nb->visited = 1;
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
