/*
 * mst.h
 * Minimum Spanning Tree via Prim's Algorithm, using our own array-based
 * min-heap (see heap.h) as the priority queue of frontier edges.
 * Prints in the same "(V,E)" format as command 10, prefixed with
 * "MST(G) = (V,E)" and followed by the total edge weight.
 */
#ifndef MST_H
#define MST_H

#include "graph.h"

/* Computes and prints the MST of the whole graph (Prim's algorithm,
   starting from the lexicographically smallest vertex). */
void graphPrintMST(Graph *g);

#endif /* MST_H */
