#include "routeSearch.h"

int *visitNode;
int *ansNodes, ansCount;
double *dis;


void initSearch(int num)
{
    visitNode = (int *) malloc(num * sizeof(int));
    dis = (double *) malloc(num * sizeof(double));
    for (int i = 0; i < num; ++ i)
    {
        visitNode[i] = 0;
        dis[i] = 1000000000;
    }
}

int dijkstra(struct link *linkList, struct edge *edgeList, const int *head, struct count *countList, int **pastNodes,
             int *nodeCount,
             struct node **nodeList, long startNode, long endNode, const char *POI, double *shortestDis)
{
    ansNodes = (int *) realloc(ansNodes, 0 * sizeof(int));

    int startNumber = findNodeIndex(*nodeList, countList->nodes, startNode),
            endNumber = findNodeIndex(*nodeList, countList->nodes, endNode);
    if (startNumber == - 1 || endNumber == - 1)
    {
        return EXIT_UNKNOWN_NODE;
    }
    initSearch(countList->nodes + 1);

    dis[startNumber] = 0;
    int *pastList = malloc(countList->nodes * sizeof(int));
    pastList[0] = startNumber;
    visitNode[0] = 1;
    int flag = (POI == NULL);
    
    search(linkList, edgeList, head, pastList, 1, 0, startNumber, endNumber, POI, flag);

    if (ansNodes == NULL)
    {
        free(visitNode);
        free(dis);
        free(pastList);
        return EXIT_UNAPPROACHABLE_NODES_PAIR;
    }

    *pastNodes = ansNodes;
    *nodeCount = ansCount;
    *shortestDis = dis[endNumber];

    free(visitNode);
    free(dis);
    free(pastList);
    
    return EXIT_NO_ERRORS;
}

void search(struct link *linkList, struct edge *edgeList, const int *head, int *pastNodes, int nodeCount, double nowDis,
            int nowNode, int endNumber, const char *POI, int flag)
{
    if (nowNode == endNumber)
    {
        if (! flag) return;
        ansCount = nodeCount;
        ansNodes = realloc(ansNodes, nodeCount * sizeof(int));
        for (int i = 0; i < nodeCount; ++ i) ansNodes[i] = pastNodes[i];
        return;
    }
    
    for (int i = head[nowNode]; i != - 1; i = edgeList[i].nxt)
    {
        if (visitNode[edgeList[i].to]) continue;
        if (nowDis + edgeList[i].length > dis[edgeList[i].to]) continue;
        
        if (linkList[edgeList[i].index].totalPOI && ! flag)
        {
            for (int j = 0; j < linkList[edgeList[i].index].totalPOI; ++ j)
            {
                if (strcmp(linkList[edgeList[i].index].POI[j], POI) == 0)
                {
                    flag = 1;
                    break;
                }
            }
        }
        
        if (flag == 1)
        {
            dis[edgeList[i].to] = nowDis + edgeList[i].length;
            pastNodes[nodeCount] = edgeList[i].to;
            visitNode[edgeList[i].to] = 1;
            search(linkList, edgeList, head, pastNodes, nodeCount + 1, dis[edgeList[i].to], edgeList[i].to, endNumber,
                   POI, flag);
            visitNode[edgeList[i].to] = 0;
        }
        
        else
        {
            pastNodes[nodeCount] = nowNode;
            visitNode[edgeList[i].to] = 1;
            pastNodes[nodeCount] = edgeList[i].to;
            search(linkList, edgeList, head, pastNodes, nodeCount + 1,
                   nowDis + edgeList[i].length, edgeList[i].to, endNumber, POI, flag);
            visitNode[edgeList[i].to] = 0;
        }
    }
}
