#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "shortestpath.h"
#include "heap.h"

void graphShortestPath(Graph *g, char *name1, char *name2)
{
    Vertex *src = graphFindVertex(g, name1);
    Vertex *dst = graphFindVertex(g, name2);
    if (src == NULL || dst == NULL)
    {
        return; /* spec does not define output for a nonexistent vertex; print nothing */
    }

    /* initialize scratch fields */
    LLNode *vn = g->vertices->head;
    while (vn != NULL)
    {
        Vertex *v = (Vertex *)vn->data;
        v->dist = INT_MAX;
        v->pred = NULL;
        v->visited = 0; /* reused here to mean "finalized" */
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
            continue; /* stale entry (a shorter distance was already finalized) */
        }
        u->visited = 1;

        if (u == dst)
        {
            break; /* shortest distance to destination finalized */
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

    if (dst->dist == INT_MAX)
    {
        return; /* spec does not define output for an unreachable destination; print nothing */
    }

    /* reconstruct the path by walking predecessors back to the source.
       Path length can never exceed the number of vertices, so that's
       exactly how big this array needs to be. */
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
