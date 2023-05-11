#include <stdio.h>
#include <malloc.h>
#include "mapEdit.h"
#include "errReport.h"
#include "dataStructure.h"

int readFile(char *filename, struct link **linkList, struct node **nodeList, struct way **wayList,
             struct geom **geomList, struct edge **edgeList, int **head, struct count *countList,
             struct bound *boundData);

void freeData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head);

void initData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head, struct count *countList);

struct link readLink(char *inputStr);

struct node readNode(char *inputStr);

struct way readWay(char *inputStr);

struct geom readGeom(char *input);

void dealEdges(struct link **linkList, struct node **nodeList,
               struct way **wayList, struct edge **edgeList, int **head, struct count *countList);
