#ifndef XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H
#define XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H

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

#endif //XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H
