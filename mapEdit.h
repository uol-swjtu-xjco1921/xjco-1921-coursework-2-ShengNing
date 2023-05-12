#include <stdio.h>
#include <malloc.h>
#include "errReport.h"
#include "dataStructure.h"

int addLink(struct link *linkList, struct count *countList, struct link *addedLink);
int addNode(struct node *nodeList, struct count *countList, struct node *addedNode);
int addWay(struct way *wayList, struct count *countList, struct way *addedWay);
int addGeom(struct geom *geomList, struct count *countList, struct geom *addedGeom);