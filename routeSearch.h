#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "routeShown.h"
#include "dataStructure.h"
#include "routeInit.h"


void initSearch(int num);

int dijkstra(struct link *linkList, struct edge *edgeList, const int *head, struct count *countList, int **pastNodes,
             int *nodeCount, struct node **nodeList, long startNode, long endNode, const char *POI,
             double *shortestDis);

void search(struct link *linkList, struct edge *edgeList, const int *head, int *pastNodes, int nodeCount, double nowDis,
            int nowNode, int endNumber, const char *POI, int flag);