#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shortestpath.h"
#include "heap.h"

#define INF 2147483647 

void graphShortestPath(Graph *g, char *name1, char *name2)
{
    Vertex *src = graphFindVertex(g, name1);
    Vertex *dst = graphFindVertex(g, name2);
    if (src == NULL || dst == NULL)
    {
        return;
    }


    LLNode *vn = g->vertices->head;
    while (vn != NULL)
    {
        Vertex *v = (Vertex *)vn->data;
        v->dist = INF;
        v->pred = NULL;
        v->visited = 0;
        vn = vn->next;
    }

    src->dist = 0;

    Heap *pq = (Heap *)malloc(sizeof(Heap));
    createHeap(pq);
    heapPush(pq, src, 0);

    while (!heapIsEmpty(pq))
    {
        Vertex *u = (Vertex *)heapPop(pq);

        if (u->visited)
        {
            continue;
        }
        u->visited = 1;

        if (u == dst)
        {
            break;
        }

        LLNode *en = u->edges->head;
        while (en != NULL)
        {
            Edge *e = (Edge *)en->data;
            Vertex *nb = graphFindVertex(g, e->neighbor);
            if (nb != NULL && !nb->visited)
            {
                int newDist = u->dist + e->weight;
                if (newDist < nb->dist)
                {
                    nb->dist = newDist;
                    nb->pred = u;
                    heapPush(pq, nb, newDist);
                }
            }
            en = en->next;
        }
    }
    free(pq);

    if (dst->dist == INF)
    {
        return;
    }


    Vertex **path = (Vertex **)malloc(sizeof(Vertex *) * g->vertexCount);
    int len = 0;
    Vertex *cur = dst;
    while (cur != NULL)
    {
        path[len] = cur;
        len++;
        if (cur == src)
        {
            break;
        }
        cur = cur->pred;
    }

    int i;
    for (i = len - 1; i >= 0; i--)
    {
        printf("%s", path[i]->name);
        if (i > 0)
        {
            printf(" -> ");
        }
    }
    printf("; Total edge cost = %d\n", dst->dist);

    free(path);
}
