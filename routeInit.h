#include <stdio.h>
#include "errReport.h"
#include "dataStructure.h"

void routeInit();
int addEdge(struct edge **edgeList, int **head, struct count *countList, struct link *addedLink);
void dealEdges(struct link **linkList, struct node **nodeList,
               struct way **wayList, struct edge **edgeList, int **head, struct count *countList);
int findIndex(long *arr, long value);