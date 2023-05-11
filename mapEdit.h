#include <stdio.h>

#include "mapRead.h"

void addLink(struct link **linkList, struct count *countList, struct link addedLink);
void addNode(struct node **nodeList, struct count *countList, struct node addedNode);
void addWay(struct way **wayList, struct count *countList, struct way addedWay);
void addGeom(struct geom **geomList, struct count *countList, struct geom addedGeom);
void addEdge(struct edge **edgeList, int **head,struct count *countList, struct link addedLink);