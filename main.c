/*
 * main.c
 * CCDSALG MCO2 - Graph Implementation
 * Reads commands from stdin in a loop and prints only the required
 * output (no prompts), as mandated by the specification.
 *
 * No goto statements are used, per the specification.
 */
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
            case 1: /* Add Vertex */
                if (scanf("%299s", name1) != 1) {
                    running = 0;
                    break;
                }
                graphAddVertex(g, name1);
                break;

            case 2: /* Add Edge */
                if (scanf("%299s %299s %d", name1, name2, &weight) != 3) {
                    running = 0;
                    break;
                }
                graphAddEdge(g, name1, name2, weight);
                break;

            case 3: /* Get Degree */
                if (scanf("%299s", name1) != 1) {
                    running = 0;
                    break;
                }
                printf("%d\n", graphGetDegree(g, name1));
                break;

            case 4: /* Edge Check */
                if (scanf("%299s %299s", name1, name2) != 2) {
                    running = 0;
                    break;
                }
                printf("%d\n", graphEdgeCheck(g, name1, name2));
                break;

            case 5: /* BFS */
                if (scanf("%299s", name1) != 1) {
                    running = 0;
                    break;
                }
                graphBFS(g, name1);
                break;

            case 6: /* DFS */
                if (scanf("%299s", name1) != 1) {
                    running = 0;
                    break;
                }
                graphDFS(g, name1);
                break;

            case 7: /* Path Check */
                if (scanf("%299s %299s", name1, name2) != 2) {
                    running = 0;
                    break;
                }
                printf("%d\n", graphPathCheck(g, name1, name2));
                break;

            case 8: /* MST */
                graphPrintMST(g);
                break;

            case 9: /* BONUS: Shortest Path */
                if (scanf("%299s %299s", name1, name2) != 2) {
                    running = 0;
                    break;
                }
                graphShortestPath(g, name1, name2);
                break;

            case 10: /* Print Graph */
                graphPrint(g);
                break;

            case 11: /* End program */
                running = 0;
                break;

            default:
                break;
        }
    }

    graphFree(g);
    return 0;
}
