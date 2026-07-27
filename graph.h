/*
 * graph.h
 * Undirected, weighted graph implemented using an adjacency list.
 * Both the vertex list and each vertex's edge list are our own
 * linked list (see linkedlist.h), kept sorted alphabetically by name
 * so that traversal tie-breaking (BFS/DFS) and printing (command 10)
 * are simple and correct.
 */
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
    LinkedList *edges; /* list of Edge*, sorted ascending by neighbor name */
    int visited;         /* scratch flag used by traversal/MST algorithms */
    int dist;             /* scratch field used by Dijkstra's algorithm */
    struct Vertex *pred;  /* scratch field used by Dijkstra's algorithm */
} Vertex;

typedef struct Graph {
    LinkedList *vertices; /* list of Vertex*, sorted ascending by name */
    int vertexCount;
} Graph;

/* Creates an empty graph. */
Graph *createGraph(void);

/* Finds a vertex by name. Returns NULL if it does not exist. */
Vertex *graphFindVertex(Graph *g, char *name);

/* Adds a vertex if it does not already exist. Returns the (new or existing) vertex. */
Vertex *graphAddVertex(Graph *g, char *name);

/*
 * Adds an undirected edge between name1 and name2 with the given weight.
 * Per the spec, both vertices are assumed to already exist (added via
 * command 1); if either does not exist, the call is silently ignored.
 * If the edge already exists, its weight is updated.
 */
void graphAddEdge(Graph *g, char *name1, char *name2, int weight);

/* Returns the degree (number of incident edges) of a vertex, or 0 if not found. */
int graphGetDegree(Graph *g, char *name);

/* Returns 1 if name1 and name2 are directly connected by an edge, 0 otherwise. */
int graphEdgeCheck(Graph *g, char *name1, char *name2);

/* Finds the Edge record from 'from' to 'to' in from's adjacency list, or NULL. */
Edge *graphFindEdge(Graph *g, char *from, char *to);

/* Prints the graph definition in the required "G = (V,E)" format. */
void graphPrint(Graph *g);

/* Frees all memory owned by the graph. */
void graphFree(Graph *g);

#endif /* GRAPH_H */
