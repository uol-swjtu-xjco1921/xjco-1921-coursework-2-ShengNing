#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include "errReport.h"
#include "dataStructure.h"

int cmpLink(const void *a, const void *b);

int cmpNode(const void *a, const void *b);

int cmpWayAndGeom(const void *a, const void *b);

void sortData(struct link **linkList, struct node **nodeList, long **wayIndex,
              long **geomIndex, struct count *countList);

int checkLink(struct node **nodeList, struct count *countList, struct link tmpLink);

int detectData(struct bound *boundData, struct link **linkList, struct node **nodeList, struct way **wayList,
               struct geom **geomList, struct count *countList, long **wayIndex, long **geomIndex);

void routeInit(struct link **linkList, struct node **nodeList,
               struct edge **edgeList, int **head, struct count *countList, int isSpeed);

void initSpeed(struct link **linkList, struct count *countList);

void addEdge(int linkNumber, struct edge *edgeList, struct node **nodeList, int *head, struct count *countList,
             struct link *addedLink);

void dealEdges(struct link **linkList, struct node **nodeList,
               long **wayIndex, struct edge **edgeList, int **head, struct count *countList);

int findLinkIndex(struct link *linkList, int limit, long id);

int findNodeIndex(struct node *nodeList, int limit, long id);

int findWayOrGeomIndex(const long *arr, int limit, long id);