/*
 * shortestpath.h
 * BONUS: Shortest path between two vertices via Dijkstra's Algorithm,
 * using our own array-based min-heap (see heap.h) as the priority queue.
 */
#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "graph.h"

/*
 * Computes the shortest path from name1 to name2 and prints it as:
 *   name1 -> ... -> name2; Total edge cost = <weight>
 * The spec does not define output for a nonexistent vertex or an
 * unreachable destination, so nothing is printed in those cases.
 */
void graphShortestPath(Graph *g, char *name1, char *name2);

#endif /* SHORTESTPATH_H */
