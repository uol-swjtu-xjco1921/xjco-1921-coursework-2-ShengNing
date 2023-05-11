#include <stdio.h>
#include <malloc.h>
#include "errReport.h"

struct link
{
    int id;
    int node1, node2;
    double length, veg, arch, land;
    char *POI;
};

struct node
{
    int id;
    double lat, lon;
};

struct way
{
    int id;
    int *nodes;
};

struct geom
{
    int id;
    int *nodes;
};

struct edge
{
    int to, nxt;
    double length, speedLimit;
    char *POI;
};

struct count
{
    int links, nodes, ways, geoms, edges;
};

struct bound
{
    double minLat, maxLat, minLon, maxLon;
};

int readFile(char *filename, struct link **linkList, struct node **nodeList, struct way **wayList,
             struct geom **geomList, struct edge **edgeList, int **head, struct count *countList,
             struct bound *boundData);

void freeData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head);

void initData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head, struct count *countList);

struct link readLink(char *inputStr, struct link **linkList, struct count *countList);

struct node readNode(char *inputStr, struct node **nodeList, struct count *countList);

struct way readWay(char *inputStr, struct way **wayList, struct count *countList);

struct geom readGeom(char *input, struct geom **geomList, struct count *countList);

void dealEdges(struct link **linkList, struct node **nodeList,
               struct way **wayList, struct edge **edgeList, int **head, struct count *countList);
