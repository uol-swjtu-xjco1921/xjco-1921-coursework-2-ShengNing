#include "routeSearch.h"

int *visitNode;
double *dis;

void initSearch(int num)
{
    visitNode = malloc(num * sizeof(int));
    dis = malloc(num * sizeof(double));
    memset(visitNode, - 1, num);
    memset(dis, 0x3f, num);
}

void dijkstra(struct edge *edgeList, int *head, struct count *countList, int *pastNode,
              long startNode, long endNode, char *POI)
{
    /*int startIndex = findIndex(nodeIndex, startNode),
            endIndex = findIndex(nodeIndex, endNode);
    pastNode[0] = startIndex;
    
    initSearch(countList->nodeIndex + 1);
    
    dis[startIndex] = 0;
    search(edgeList, head, pastNode, 0, startIndex, endIndex, POI, 0);*/
    
}

void search(struct edge *edgeList, int *head, int *pastNode, double nowDis,
            int nowNode, int endIndex, char *POI, int flag)
{
    if (nowNode == endIndex)
    {
        if (! flag) return;
        
    }
    
    for (int i = head[nowNode]; i != - 1; i = edgeList[i].nxt)
    {
        if (visitNode[edgeList[i].to]) continue;
        if (dis[nowNode] + edgeList[i].length > dis[edgeList[i].to]) continue;
        
    }
}