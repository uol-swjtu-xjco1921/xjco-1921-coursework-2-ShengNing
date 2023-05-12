#ifndef XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H
#define XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H

struct link
{
    long id;
    long node1, node2;
    long way;
    int totalPOI;
    double length, veg, arch, land;
    char **POI;
};

struct node
{
    long id;
    double lat, lon;
};

struct way
{
    long id;
    int size;
    long *nodes;
};

struct geom
{
    long id;
    int size;
    long *nodes;
};

struct edge
{
    long id;
    long to, nxt;
    long way;
    int totalPOI;
    double length, speedLimit;
    char **POI;
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
