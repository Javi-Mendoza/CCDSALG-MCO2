#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"

Graph *createGraph(void)
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertices = llCreate();
    g->vertexCount = 0;
    return g;
}

Vertex *graphFindVertex(Graph *g, char *name)
{
    
     //linear search and strcmp
    LLNode *node = g->vertices->head;
    while (node != NULL)
    {
        Vertex *v = (Vertex *)node->data;
        if (strcmp(v->name, name) == 0)
        {
            return v;
        }
        node = node->next;
    }
    return NULL;
}


//inserts new vertex into list and keeps list sorted alphabeticaly
void insertVertexSorted(Graph *g, Vertex *v)
{
    LinkedList *list = g->vertices;

    LLNode *newNode = (LLNode *)malloc(sizeof(LLNode));
    newNode->data = v;
    newNode->next = NULL;

    if (list->head == NULL || strcmp(v->name, ((Vertex *)list->head->data)->name) < 0)
    {
       //put new vertex infront of list
        newNode->next = list->head;
        list->head = newNode;
        if (list->tail == NULL)
        {
            list->tail = newNode;
        }
        list->size++;
        return;
    }

    LLNode *cur = list->head;
    while (cur->next != NULL && strcmp(v->name, ((Vertex *)cur->next->data)->name) >= 0)
    {
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    if (newNode->next == NULL)
    {
        list->tail = newNode;
    }
    list->size++;
}


//same with insert vertex sorted but for edge
void insertEdgeSorted(LinkedList *list, Edge *e)
{
    LLNode *newNode = (LLNode *)malloc(sizeof(LLNode));
    newNode->data = e;
    newNode->next = NULL;

    if (list->head == NULL || strcmp(e->neighbor, ((Edge *)list->head->data)->neighbor) < 0)
    {
        newNode->next = list->head;
        list->head = newNode;
        if (list->tail == NULL)
        {
            list->tail = newNode;
        }
        list->size++;
        return;
    }

    LLNode *cur = list->head;
    while (cur->next != NULL && strcmp(e->neighbor, ((Edge *)cur->next->data)->neighbor) >= 0)
    {
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    if (newNode->next == NULL)
    {
        list->tail = newNode;
    }
    list->size++;
}

Vertex *graphAddVertex(Graph *g, char *name)
{
    Vertex *existing = graphFindVertex(g, name);
    if (existing != NULL)
    {
        return existing;
    }
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    strncpy(v->name, name, MAX_NAME_LEN);
    v->name[MAX_NAME_LEN] = '\0';
    v->edges = llCreate();
    v->visited = 0;

    insertVertexSorted(g, v);
    g->vertexCount++;
    return v;
}

Edge *graphFindEdge(Graph *g, char *from, char *to)
{
    Vertex *v = graphFindVertex(g, from);
    if (v == NULL)
    {
        return NULL;
    }
    LLNode *node = v->edges->head;
    while (node != NULL)
    {
        Edge *e = (Edge *)node->data;
        if (strcmp(e->neighbor, to) == 0)
        {
            return e;
        }
        node = node->next;
    }
    return NULL;
}

void addDirectedEdge(Graph *g, char *from, char *to, int weight)
{
    Vertex *v = graphFindVertex(g, from);
    if (v == NULL)
    {
        return;
    }
    Edge *existing = graphFindEdge(g, from, to);
    if (existing != NULL)
    {
        existing->weight = weight; //readding edge updates weight
        return;
    }
    Edge *e = (Edge *)malloc(sizeof(Edge));
    strncpy(e->neighbor, to, MAX_NAME_LEN);
    e->neighbor[MAX_NAME_LEN] = '\0';
    e->weight = weight;
    insertEdgeSorted(v->edges, e);
}

void graphAddEdge(Graph *g, char *name1, char *name2, int weight)
{
    if (graphFindVertex(g, name1) == NULL || graphFindVertex(g, name2) == NULL)
    {
        return;
    }
    addDirectedEdge(g, name1, name2, weight);
    addDirectedEdge(g, name2, name1, weight);
}

int graphGetDegree(Graph *g, char *name)
{
    Vertex *v = graphFindVertex(g, name);
    if (v == NULL)
    {
        return 0;
    }
    return v->edges->size;
}

int graphEdgeCheck(Graph *g, char *name1, char *name2)
{
    if (graphFindEdge(g, name1, name2)!=NULL){
    return 1;
    }else{
    return 0;
}
}

void graphPrint(Graph *g)
{
    printf("G = (V,E)\n");

    printf("V = {");
    LLNode *vn = g->vertices->head;
    int first = 1;
    while (vn != NULL)
    {
        Vertex *v = (Vertex *)vn->data;
        if (!first)
        {
            printf(", ");
        }
        printf("%s", v->name);
        first = 0;
        vn = vn->next;
    }
    printf("}\n");

    printf("E = {\n");
    vn = g->vertices->head;
    while (vn != NULL)
    {
        Vertex *v = (Vertex *)vn->data;
        LLNode *en = v->edges->head;
        while (en != NULL)
        {
            Edge *e = (Edge *)en->data;
            if (strcmp(v->name, e->neighbor) < 0)
            {
                printf("    (%s, %s, %d),\n", v->name, e->neighbor, e->weight);
            }
            en = en->next;
        }
        vn = vn->next;
    }
    printf("}\n");
}

void graphFree(Graph *g)
{
    if (g == NULL)
    {
        return;
    }

    LLNode *vn = g->vertices->head;
    while (vn != NULL)
    {
        Vertex *v = (Vertex *)vn->data;

        LLNode *en = v->edges->head;
        while (en != NULL)
        {
            Edge *e = (Edge *)en->data;
            free(e);
            en = en->next;
        }
        llFree(v->edges);
        free(v);

        vn = vn->next;
    }
    llFree(g->vertices);
    free(g);
}
