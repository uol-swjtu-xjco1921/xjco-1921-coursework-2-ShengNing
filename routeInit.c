#include "routeInit.h"

int cmpLink(const void *a, const void *b)
{
    struct link c = *(struct link *) a;
    struct link d = *(struct link *) b;
    return c.id > d.id;
}

int cmpNode(const void *a, const void *b)
{
    struct node c = *(struct node *) a;
    struct node d = *(struct node *) b;
    return c.id > d.id;
}

int cmpWayAndGeom(const void *a, const void *b)
{
    long long *c = (long long *) a;
    long long *d = (long long *) b;
    return *c > *d ? 1 : (*c == *d ? 0 : - 1);
}

void sortData(struct link **linkList, struct node **nodeList, long **wayIndex,
              long **geomIndex, struct count *countList)
{
    qsort(*linkList, countList->links, sizeof(*linkList[0]), cmpLink);
    qsort(*nodeList, countList->nodes, sizeof(*nodeList[0]), cmpNode);
    qsort(*wayIndex, countList->ways, sizeof(long), cmpWayAndGeom);
    qsort(*geomIndex, countList->geoms, sizeof(long), cmpWayAndGeom);
}

int checkLink(struct node **nodeList, struct count *countList, struct link tmpLink)
{
    int node1Number, node2Number;
    node1Number = findNodeIndex(*nodeList, countList->nodes, tmpLink.node1);
    node2Number = findNodeIndex(*nodeList, countList->nodes, tmpLink.node2);
    
    if (node1Number == - 1 || node2Number == - 1)
        return EXIT_UNKNOWN_NODE;
    return EXIT_NO_ERRORS;
}

int detectData(struct bound *boundData, struct link **linkList, struct node **nodeList, struct way **wayList,
               struct geom **geomList, struct count *countList, long **wayIndex, long **geomIndex)
{
    // verify bounding
    if (boundData->minLat > boundData->maxLat || boundData->minLon > boundData->maxLon)
        return EXIT_BAD_BOUNDING;
    
    // verify link
    for (int i = 0; i < (countList->links); ++ i)
    {
        if (i + 1 < (countList->links))
            if ((*linkList + i)->id == (*linkList + i + 1)->id)
                return EXIT_REPEAT_ID;
        
        int returnValue = checkLink(nodeList, countList, *(*linkList + i));
        if (returnValue)
            return returnValue;
    }
    // verify node
    for (int i = 0; i < (countList->nodes); ++ i)
    {
        if (i + 1 < (countList->ways))
            if ((*nodeList + i)->id == (*nodeList + i + 1)->id)
                return EXIT_REPEAT_ID;
    }
    // verify way
    for (int i = 0; i < (countList->ways); ++ i)
    {
        if (i + 1 < (countList->ways))
            if (*(*wayIndex + i) == *(*wayIndex + i + 1))
                return EXIT_REPEAT_ID;
        int wayNumber = findWayOrGeomIndex(*wayIndex, countList->ways, *(*wayIndex + i));
        for (int j = 0; j < (*wayList + wayNumber)->size; ++ j)
        {
            int nodeNumber = findNodeIndex(*nodeList, countList->nodes, ((*wayList + wayNumber)->nodes[j]));
            if (nodeNumber == - 1)
                return EXIT_UNKNOWN_NODE;
        }
    }
    // verify geom
    for (int i = 0; i < (countList->geoms); ++ i)
    {
        if (i + 1 < (countList->geoms))
            if (*(*geomIndex + i) == *(*geomIndex + i + 1))
                return EXIT_REPEAT_ID;
        int geomNumber = findWayOrGeomIndex(*geomIndex, countList->geoms, *(*geomIndex + i));
        for (int j = 0; j < (*geomList + geomNumber)->size; ++ j)
        {// fix: *
            int nodeNumber = findNodeIndex(*nodeList, countList->nodes, ((*geomList + geomNumber)->nodes[j]));
            if (nodeNumber == - 1)
                return EXIT_UNKNOWN_NODE;
        }
    }
    return EXIT_NO_ERRORS;
}

void routeInit(struct link **linkList, struct node **nodeList,
               struct edge **edgeList, int **head, struct count *countList, int isSpeed)
{
    
    int linkNumber = findLinkIndex(*linkList, countList->links, (*edgeList)->id);
    // nowType == 0: length
    // nowType == 1: speed
    int nowType = ((*linkList + linkNumber)->length == (*edgeList)->length) ^ 1;
    
    
    if ((isSpeed ^ nowType) == 0)
    {
        return;
    }
    
    if (isSpeed)
    {
        for (int i = 0; i < (countList->edges); ++ i)
        {
            linkNumber = findLinkIndex(*linkList, countList->links, (*edgeList + i)->id);
            (*edgeList + i)->length /= (*linkList + linkNumber)->speedLimit;
        }
    }
    
    else
    {
        for (int i = 0; i < (countList->edges); ++ i)
        {
            linkNumber = findLinkIndex(*linkList, countList->links, (*edgeList + i)->id);
            (*edgeList + i)->length = (*linkList + linkNumber)->length;
        }
    }
}

void initSpeed(struct link **linkList, struct count *countList)
{
    for (int i = 0; i < (countList->links); ++ i)
    {
        // speedLimit is initially set as 60.0 km/h.
        if((*linkList + i)->speedLimit) continue;
        (*linkList + i)->speedLimit = 60.0;
    }
}

void addEdge(int linkNumber, struct edge *edgeList, struct node **nodeList, int *head, struct count *countList,
             struct link *addedLink)
{
    
    int node1Index = findNodeIndex(*nodeList, countList->nodes, addedLink->node1),
            node2Index = findNodeIndex(*nodeList, countList->nodes, addedLink->node2);
    
    struct edge tmpEdge1 = {addedLink->id, linkNumber, node2Index, head[node1Index], addedLink->length};
    edgeList[countList->edges] = tmpEdge1, head[node1Index] = countList->edges;
    
    struct edge tmpEdge2 = {addedLink->id, linkNumber, node1Index, head[node2Index], addedLink->length};
    edgeList[countList->edges + 1] = tmpEdge2, head[node2Index] = countList->edges + 1;
}

void dealEdges(struct link **linkList, struct node **nodeList,
               long **wayIndex, struct edge **edgeList, int **head, struct count *countList)
{
    *head = malloc(countList->nodes * sizeof(int));
    for (int i = 0; i < countList->nodes; ++ i) *(*head + i) = - 1;
    for (int i = 0; i < (countList->links); ++ i)
    {
        int wayNumber = findWayOrGeomIndex(*wayIndex, countList->ways, (*linkList + i)->way);
        if (wayNumber == - 1) continue;
        int linkNumber = findLinkIndex(*linkList, countList->links, (*linkList + i)->id);
        
        *edgeList = realloc(*edgeList, (countList->edges + 2) * sizeof(struct edge));
        addEdge(linkNumber, *edgeList, nodeList, *head, countList, (*linkList + i));
        countList->edges += 2;
        
    }
}

int findLinkIndex(struct link *linkList, int limit, long id)
{
    int l = 0, r = limit, ans = - 1;
    while (l < r)
    {
        
        int mid = (l + r) / 2;
        if (linkList[mid].id >= id) r = mid;
        else l = mid + 1;
        if (linkList[mid].id == id) ans = mid;
    }
    return ans;
}

int findNodeIndex(struct node *nodeList, int limit, long id)
{
    int l = 0, r = limit, ans = - 1;
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (nodeList[mid].id >= id) r = mid;
        else l = mid + 1;
        if (nodeList[mid].id == id) ans = mid;
    }
    return ans;
}

int findWayOrGeomIndex(const long *arr, int limit, long id)
{
    int l = 0, r = limit, ans = - 1;
    while (l < r)
    {
        int mid = (l + r) / 2;
        if (arr[mid] >= id) r = mid;
        else l = mid + 1;
        if (arr[mid] == id) ans = mid;
    }
    return ans;
}