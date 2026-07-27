/*
 * traversal.h
 * Graph traversal algorithms: Breadth-First Search (using our Queue),
 * Depth-First Search (using our Stack), and a path/connectivity check
 * built on top of BFS.
 *
 * Tie-breaking rule (per spec): whenever there is a choice between two
 * adjacent vertices, the lexicographically smaller name is visited first.
 * This is guaranteed by the Graph module keeping every adjacency list
 * sorted alphabetically by neighbor name.
 */
#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "graph.h"

/* Prints the BFS order starting at 'start', one vertex name per line. */
void graphBFS(Graph *g, char *start);

/* Prints the DFS order starting at 'start', one vertex name per line. */
void graphDFS(Graph *g, char *start);

/* Returns 1 if name2 is reachable from name1 (or they are equal), 0 otherwise. */
int graphPathCheck(Graph *g, char *name1, char *name2);

#endif /* TRAVERSAL_H */
