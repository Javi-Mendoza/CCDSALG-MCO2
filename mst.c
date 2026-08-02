#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mst.h"
#include "heap.h"

typedef struct {
    char from[MAX_NAME_LEN + 1];
    char to[MAX_NAME_LEN + 1];
    int weight;
} FrontierEdge;

typedef struct {
    char u[MAX_NAME_LEN + 1];
    char v[MAX_NAME_LEN + 1];
    int weight;
} MstEdge;

void sortMSTEdges(MstEdge edges[], int n)
{
    int i, j;
    for (i = 1; i < n; i++)
    {
        MstEdge key = edges[i];
        j = i - 1;
        while (j >= 0 &&
               (strcmp(edges[j].u, key.u) > 0 ||
                (strcmp(edges[j].u, key.u) == 0 && strcmp(edges[j].v, key.v) > 0)))
        {
            edges[j + 1] = edges[j];
            j--;
        }
        edges[j + 1] = key;
    }
}

void graphPrintMST(Graph *g)
{
    if (g->vertices->head == NULL)
    {
        printf("MST(G) = (V,E)\n");
        printf("V = {}\n");
        printf("E = {\n}\n");
        printf("Total Edge Weight: 0\n");
        return;
    }

    LLNode *vn = g->vertices->head;
    while (vn != NULL)
    {
        ((Vertex *)vn->data)->visited = 0;
        vn = vn->next;
    }

    Vertex *startV = (Vertex *)g->vertices->head->data;
    startV->visited = 1;

    Heap *pq = (Heap *)malloc(sizeof(Heap));
    createHeap(pq);

    MstEdge *result = (MstEdge *)malloc(sizeof(MstEdge) * g->vertexCount);
    int resultCount = 0;
    int totalWeight = 0;

    LLNode *en = startV->edges->head;
    while (en != NULL)
    {
        Edge *e = (Edge *)en->data;
        FrontierEdge *fe = (FrontierEdge *)malloc(sizeof(FrontierEdge));
        strcpy(fe->from, startV->name);
        strcpy(fe->to, e->neighbor);
        fe->weight = e->weight;
        heapPush(pq, fe, fe->weight);
        en = en->next;
    }

    int verticesInTree = 1;
    while (!heapIsEmpty(pq) && verticesInTree < g->vertexCount)
    {
        FrontierEdge *fe = (FrontierEdge *)heapPop(pq);
        Vertex *toV = graphFindVertex(g, fe->to);

        if (toV == NULL || toV->visited)
        {
            free(fe);
            continue;
        }

        toV->visited = 1;
        verticesInTree++;

        MstEdge me;
        if (strcmp(fe->from, fe->to) < 0)
        {
            strcpy(me.u, fe->from);
            strcpy(me.v, fe->to);
        }
        else
        {
            strcpy(me.u, fe->to);
            strcpy(me.v, fe->from);
        }
        me.weight = fe->weight;
        result[resultCount] = me;
        resultCount++;
        totalWeight += fe->weight;

        LLNode *ten = toV->edges->head;
        while (ten != NULL)
        {
            Edge *e = (Edge *)ten->data;
            Vertex *nb = graphFindVertex(g, e->neighbor);
            if (nb != NULL && !nb->visited)
            {
                FrontierEdge *newFe = (FrontierEdge *)malloc(sizeof(FrontierEdge));
                strcpy(newFe->from, toV->name);
                strcpy(newFe->to, e->neighbor);
                newFe->weight = e->weight;
                heapPush(pq, newFe, newFe->weight);
            }
            ten = ten->next;
        }
        free(fe);
    }

    while (!heapIsEmpty(pq))
    {
        FrontierEdge *fe = (FrontierEdge *)heapPop(pq);
        free(fe);
    }
    free(pq);

    sortMSTEdges(result, resultCount);

    printf("MST(G) = (V,E)\n");
    printf("V = {");
    vn = g->vertices->head;
    int first = 1;
    while (vn != NULL)
    {
        Vertex *v = (Vertex *)vn->data;
        if (v->visited) 
        {
            if (!first)
            {
                printf(", ");
            }
            printf("%s", v->name);
            first = 0;
        }
        vn = vn->next;
    }
    printf("}\n");

    printf("E = {\n");
    int i;
    for (i = 0; i < resultCount; i++)
    {
        printf("    (%s, %s, %d),\n", result[i].u, result[i].v, result[i].weight);
    }
    printf("}\n");
    printf("Total Edge Weight: %d\n", totalWeight);

    free(result);
}
