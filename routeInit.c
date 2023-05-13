#include "routeInit.h"

double distance(struct node a, struct node b)
{
    return sqrt((a.lon - b.lon) * (a.lon - b.lon) + (a.lat - b.lat) * (a.lat - b.lat));
}

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

int detectData(struct link **linkList, struct node **nodeList, struct way **wayList,
               struct geom **geomList, struct count *countList, long **wayIndex, long **geomIndex)
{
    // verify link
    for (int i = 0; i < (countList->links); ++ i)
    {
        if (i + 1 < (countList->links))
            if ((*linkList + i)->id == (*linkList + i + 1)->id)
                return EXIT_REPEAT_ID;
        
        int node1Number, node2Number;
        node1Number = findNodeIndex(*nodeList, countList->nodes, (*linkList + i)->node1);
        node2Number = findNodeIndex(*nodeList, countList->nodes, (*linkList + i)->node2);
        if (node1Number == - 1 || node2Number == - 1)
            return EXIT_UNKNOWN_NODE;
        
//        if ((*linkList + i)->length - distance(*(*nodeList + node1Number), *(*nodeList + node2Number)) > 1e-6)
//        {
//            printf("%ld %ld\n",(*linkList + i)->id, (*nodeList + node2Number)->id);
//            printf("%lf %lf\n", (*linkList + i)->length, distance(*(*nodeList + node1Number), *(*nodeList + node2Number)));
//            printf("%lf %lf %lf %lf\n", (*nodeList + node1Number)->lat, (*nodeList + node1Number)->lon, (*nodeList + node2Number)->lat, (*nodeList + node2Number)->lon);
//            return EXIT_UNMATCHED_LENGTH;
//        }
         
//         int wayNumber = findWayOrGeomIndex(*wayIndex, countList->ways, (*linkList + i)->way);
//
//         if (wayNumber == - 1)
//         {
//             printf("%ld\n", (*linkList + i)->way);
//             return EXIT_UNKNOWN_WAY;
//         }
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
            if ((*wayIndex + i) == (*wayIndex + i + 1))
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
            if ((*geomIndex + i) == (*geomIndex + i + 1))
                return EXIT_REPEAT_ID;
        int geomNumber = findWayOrGeomIndex(*geomIndex, countList->geoms, *(*geomIndex + i));
        for (int j = 0; j < (*geomList + geomNumber)->size; ++ j)
        {
            int nodeNumber = findNodeIndex(*nodeList, countList->nodes, ((*geomList + geomNumber)->nodes[j]));
            if (nodeNumber == - 1)
                return EXIT_UNKNOWN_NODE;
        }
    }
    return EXIT_NO_ERRORS;
}

void routeInit()
{

}

void initSpeed()
{

}

void addEdge(struct edge *edgeList, int *head, struct count *countList, struct link *addedLink)
{
    /*int node1Index = findIndex(addedLink->node1),
            node2Index = findIndex(addedLink->node2);*/
    
    // edgeList[countList->edges + 1] = {.to=node2Index, .nxt=head[node1Index]};
    
}

void dealEdges(struct link **linkList, struct node **nodeList,
               struct way **wayList, struct edge **edgeList, int **head, struct count *countList)
{
    for (int i = 0; i < (countList->links); ++ i)
    {
        *edgeList = realloc(*edgeList, (countList->edges + 2) * sizeof(struct edge));
        *head = realloc(*head, (countList->edges + 2) * sizeof(int));
        addEdge(*edgeList, *head, countList, linkList[i]);
    }
}

int findLinkIndex(struct link *linkList, int limit, long id)
{
    int l = 0, r = limit, ans = - 1;
    while (l <= r)
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