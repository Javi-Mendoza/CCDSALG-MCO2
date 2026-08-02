#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "graph.h"

void graphBFS(Graph *g, char *start);

void graphDFS(Graph *g, char *start);

int graphPathCheck(Graph *g, char *name1, char *name2);

#endif /* TRAVERSAL_H */
