#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "mapEdit.h"
#include "routeInit.h"
#include "errReport.h"
#include "dataStructure.h"

int readFile(char *filename, struct link **linkList, struct node **nodeList, struct way **wayList,
             struct geom **geomList, struct edge **edgeList, int **head, struct count *countList,
             struct bound *boundData);

void freeData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head);

void initData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head, struct count *countList);

int readBound(char *inputStr, struct bound *boundData);

int readLink(char *inputStr, struct link *tmpLink);

int readNode(char *inputStr, struct node *tmpNode);

int readWay(char *inputStr, struct way *tmpWay);

int readGeom(char *inputStr, struct geom *tmpGeom);

