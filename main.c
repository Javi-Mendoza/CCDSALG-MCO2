#include <stdio.h>
#include "graph.h"
#include "traversal.h"
#include "mst.h"
#include "shortestpath.h"

#define BUF_LEN 300

int main(void) {
    Graph *g = createGraph();
    int cmd;
    char name1[BUF_LEN];
    char name2[BUF_LEN];
    int weight;
    int running = 1;

    while (running && scanf("%d", &cmd) == 1) {
        switch (cmd) {
            case 1: // Add Vertex
                if (scanf("%299s", name1) != 1) {
                    running = 0;
                    break;
                }
                graphAddVertex(g, name1);
                break;

            case 2: // Add Edge
                if (scanf("%299s %299s %d", name1, name2, &weight) != 3) {
                    running = 0;
                    break;
                }
                graphAddEdge(g, name1, name2, weight);
                break;

            case 3: //get degree
                if (scanf("%299s", name1) != 1) {
                    running = 0;
                    break;
                }
                printf("%d\n", graphGetDegree(g, name1));
                break;

            case 4: // edge chekc
                if (scanf("%299s %299s", name1, name2) != 2) {
                    running = 0;
                    break;
                }
                printf("%d\n", graphEdgeCheck(g, name1, name2));
                break;

            case 5: //bfs
                if (scanf("%299s", name1) != 1) {
                    running = 0;
                    break;
                }
                graphBFS(g, name1);
                break;

            case 6: //dfs
                if (scanf("%299s", name1) != 1) {
                    running = 0;
                    break;
                }
                graphDFS(g, name1);
                break;

            case 7: //path chekc
                if (scanf("%299s %299s", name1, name2) != 2) {
                    running = 0;
                    break;
                }
                printf("%d\n", graphPathCheck(g, name1, name2));
                break;

            case 8: //mst
                graphPrintMST(g);
                break;

            case 9: //shorest path
                if (scanf("%299s %299s", name1, name2) != 2) {
                    running = 0;
                    break;
                }
                graphShortestPath(g, name1, name2);
                break;

            case 10: //printgraph
                graphPrint(g);
                break;

            case 11: //byebye
                running = 0;
                break;

            default:
                break;
        }
    }

    graphFree(g);
    return 0;
}
