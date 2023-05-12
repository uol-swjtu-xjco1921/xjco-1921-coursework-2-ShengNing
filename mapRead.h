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

void readLink(char *inputStr, struct link *tmpLink);

void readNode(char *inputStr, struct node *tmpNode);

void readWay(char *inputStr, struct way *tmpWay);

void readGeom(char *inputStr, struct geom *tmpGeom);

