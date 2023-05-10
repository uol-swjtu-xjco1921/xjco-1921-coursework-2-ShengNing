#include <stdio.h>
#include "errReport.h"

struct edge
{
    int to,nxt;
    double length, speedLimit;
    char *POI;
};

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

struct count
{
    int links, nodes, ways, geoms, edges;
};

int readFile(char *filename, struct link **linkList, struct node **nodeList, struct way **wayList,
        struct geom **geomList, struct count *countList);