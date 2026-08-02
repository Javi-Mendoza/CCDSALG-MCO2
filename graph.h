#ifndef GRAPH_H
#define GRAPH_H

#include "linkedlist.h"

#define MAX_NAME_LEN 256

typedef struct Edge {
    char neighbor[MAX_NAME_LEN + 1];
    int weight;
} Edge;

typedef struct Vertex {
    char name[MAX_NAME_LEN + 1];
    LinkedList *edges; //list of Edge* sorted ascending by neighbor name 
    int visited;         // scratch flag used by traversal/MST
    int dist;             // scratch field used by dijkstra
    struct Vertex *pred;  // scratch field used by dijkstra 
} Vertex;

typedef struct Graph {
    LinkedList *vertices; // list of vertex
    int vertexCount;
} Graph;


Graph *createGraph(void);

Vertex *graphFindVertex(Graph *g, char *name);

Vertex *graphAddVertex(Graph *g, char *name);

void graphAddEdge(Graph *g, char *name1, char *name2, int weight);
int graphGetDegree(Graph *g, char *name);
int graphEdgeCheck(Graph *g, char *name1, char *name2);
Edge *graphFindEdge(Graph *g, char *from, char *to);
void graphPrint(Graph *g);
void graphFree(Graph *g);

#endif /* GRAPH_H */
