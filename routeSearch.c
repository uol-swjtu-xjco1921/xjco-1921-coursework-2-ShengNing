#include "routeSearch.h"

int *visitNode;
int *ansNodes;
double *dis;


void initSearch(int num)
{
    visitNode = malloc(num * sizeof(int));
    dis = malloc(num * sizeof(double));
    memset(visitNode, - 1, num);
    memset(dis, 0x3f, num);
}

void dijkstra(struct edge *edgeList, int *head, struct count *countList, int *pastNodes, struct node **nodeList,
              long startNode, long endNode, char *POI)
{
    int startNumber = findNodeIndex(*nodeList, countList->nodes, startNode),
            endNumber = findNodeIndex(*nodeList, countList->nodes, endNode);
    pastNodes[0] = startNumber;
    
    initSearch(countList->nodeIndex + 1);
    
    dis[startNumber] = 0;
    int *pastList = malloc(countList->nodes * sizeof (int));
    pastList[0] = startNumber;

    int flag = (POI==NULL);
    search(edgeList, head, pastList, 1,0, startNumber, endNumber, POI, flag);

    *pastNodes = *ansNodes;
}

void search(struct edge *edgeList, int *head, int *pastNodes, nodeCount, double nowDis,
            int nowNode, int endNumber, char *POI, int flag)
{
    if (nowNode == endNumber)
    {
        if (! flag) return;
        free(ansNodes);
        *ansNodes = malloc(nodeCount * sizeof (int));
        ansNodes = pastNodes;
    }

    for (int i = head[nowNode]; i != - 1; i = edgeList[i].nxt)
    {
        if (visitNode[edgeList[i].to]) continue;
        if (nowDis + edgeList[i].length > dis[edgeList[i].to]) continue;
        if(flag == 1)
        {
            dis[edgeList[i].to] = nowDis + edgeList[i].length;visitNode[nowNode] = 1;
            pastNodes[nodeCount] = nowNode;
            visitNode[edgeList[i].to] = 1;
            search(edgeList, head, pastNodes, nodeCount + 1, dis[edgeList[i].to], edgeList[i].to, endNumber, POI, 1);
            visitNode[edgeList[i].to] =0;
        }
        else
        {
            pastNodes[nodeCount] = nowNode;
            visitNode[edgeList[i].to] = 1;
            search(edgeList, head, pastNodes, nodeCount + 1,
                   nowDis + edgeList[i].length, edgeList[i].to, endNumber, POI, 1);
            visitNode[edgeList[i].to] =0;
        }
    }
}