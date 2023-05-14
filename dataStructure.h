#ifndef XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H
#define XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H

struct link
{
    long id;
    long node1, node2;
    long way;
    int totalPOI;
    double length, veg, arch, land, speedLimit;
    
    int attributeCount;
    char (*attributeName)[15];
    double attribute[15];
    
    char (*POI)[100];
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
    int index;
    int to, nxt;
    double length;
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
