#ifndef XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H
#define XJCO_1921_COURSEWORK_2_SHENGNING_DATASTRUCTURE_H

#define maxPOILength 15
#define maxAttNameLength 15
#define attributeLimit 15

struct link
{
    long id;
    long node1, node2;
    long way;
    double length, speedLimit;
    
    int attributeCount;
    char attributeName[attributeLimit][maxAttNameLength];
    double attribute[attributeLimit];
    
    int totalPOI;
    char POI[attributeLimit][maxPOILength];
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
