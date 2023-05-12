#include "mapEdit.h"

int addLink(struct link **linkList, struct count *countList, struct link *addedLink)
{
    if (addedLink == NULL)
    {
        return EXIT_Bad_Data;
    }
    struct link **newLinkList = realloc(*linkList, (countList->links + 1) * sizeof(struct link));
    if (*linkList == NULL)
    {
        return EXIT_EXTRA_MEMORY;
    }
    linkList =newLinkList;
    
    *linkList[countList->links] = *addedLink;
    countList->links ++;
    printf("%ld\n", linkList[countList->links-1]->id);
    return EXIT_NO_ERRORS;
}

int addNode(struct node **nodeList, struct count *countList, struct node *addedNode)
{
    if (addedNode == NULL)
    {
        return EXIT_Bad_Data;
    }
    
    countList->nodes += 1;
    *nodeList = realloc(*nodeList, countList->nodes * sizeof(struct node));
    nodeList[countList->nodes - 1] = addedNode;
    
    return EXIT_NO_ERRORS;
}

int addWay(struct way **wayList, struct count *countList, struct way *addedWay)
{
    if (addedWay == NULL)
    {
        return EXIT_Bad_Data;
    }
    
    countList->ways += 1;
    *wayList = realloc(*wayList, countList->ways * sizeof(struct way));
    wayList[countList->ways - 1] = addedWay;
    
    return EXIT_NO_ERRORS;
}

int addGeom(struct geom **geomList, struct count *countList, struct geom *addedGeom)
{
    if (addedGeom == NULL)
    {
        return EXIT_Bad_Data;
    }
    
    countList->geoms += 1;
    *geomList = realloc(*geomList, countList->geoms * sizeof(struct geom));
    geomList[countList->geoms - 1] = addedGeom;
    
    return EXIT_NO_ERRORS;
}

