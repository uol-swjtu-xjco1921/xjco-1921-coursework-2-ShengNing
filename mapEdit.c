#include "mapEdit.h"

int addLink(struct link *linkList, struct count *countList, struct link *addedLink)
{
    linkList[countList->links] = *addedLink;
    countList->links ++;
    return EXIT_NO_ERRORS;
}

int addNode(struct node *nodeList, struct count *countList, struct node *addedNode)
{
    nodeList[countList->nodes] = *addedNode;
    countList->nodes ++;
    return EXIT_NO_ERRORS;
}

int addWay(struct way *wayList, struct count *countList, struct way *addedWay)
{
    wayList[countList->ways] = *addedWay;
    countList->ways ++;
    return EXIT_NO_ERRORS;
}

int addGeom(struct geom *geomList, struct count *countList, struct geom *addedGeom)
{
    geomList[countList->geoms] = *addedGeom;
    countList->geoms ++;
    return EXIT_NO_ERRORS;
}

