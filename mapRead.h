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

void readLink(char *inputStr, struct link * tmpLink);

struct node readNode(char *inputStr);

struct way readWay(char *inputStr);

struct geom readGeom(char *input);

