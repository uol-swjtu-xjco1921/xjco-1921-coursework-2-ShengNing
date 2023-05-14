#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "dataStructure.h"
#include "routeInit.h"

void initSearch(int num);

void dijkstra(struct edge *edgeList, int *head, struct count *countList, int *pastNodes, struct node **nodeList,
              long startNode, long endNode, char *POI);

void search(struct edge *edgeList, int *head, int *pastNodes, double nowDis,
            int nowNode, int endIndex, char *POI, int flag);