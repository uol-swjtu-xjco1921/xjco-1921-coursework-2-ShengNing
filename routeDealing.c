#include "errReport.h"
#include "mapEdit.h"
#include "routeInit.h"
#include "routeSearch.h"
#include "routeShown.h"
#include "dataStructure.h"
#include "mapRead.h"

struct link *linkList;
struct node *nodeList;
struct way *wayList;
struct geom *geomList;
struct edge *edgeList;
struct count countList;
struct bound boundData;
int *head;


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        reportErr(EXIT_WRONG_ARG_COUNT, argv[0]);
        return EXIT_WRONG_ARG_COUNT;
    }
    
    int returnValue = readFile(argv[1], &linkList, &nodeList,
                               &wayList, &geomList, &edgeList, &head, &countList, &boundData);
    if (returnValue)
    {
        freeData(&linkList, &nodeList, &wayList, &geomList, &edgeList, &head);
        reportErr(returnValue, argv[1]);
        return returnValue;
    }
    printf("The file was read successfully.\n");
    
    initSpeed(&linkList, &countList);
    
    
    while (1)
    {
        system("clear");
        printf("Enter the number to select the function.\n");
        printf("1. Query the shortest path of two points.\n");
        printf("2. Query the fastest path between two points.\n");
        printf("3. Query the shortest path between two points, through a particular POI.\n");
        printf("0. Exit.\n");
        char input[100];
        scanf("%s", input);
        long value = strtol(input, NULL, 10);
        if (value == 0)
        {
            printf("Exit?.\n");
            printf("1. Exit.\n");
            printf("0. Back.\n");
            scanf("%s", input);
            value = strtol(input, NULL, 10);
            if (value == 1) break;
            else continue;
        }
        if (value == 1)
        {
            long startNode, endNode;
            double shortestDis = 0;
            int *pastNodes = NULL, nodeCount;
            char *POI = NULL;
            printf("Enter the id of first node.\n");
            scanf("%s", input);
            startNode = strtol(input, NULL, 10);
            printf("Enter the id of second node.\n");
            scanf("%s", input);
            endNode = strtol(input, NULL, 10);
            
            routeInit(&linkList, &nodeList, &edgeList, &head, &countList, 0);
            
            returnValue = dijkstra(linkList, edgeList, head, &countList, &pastNodes, &nodeCount, &nodeList, startNode,
                                   endNode, POI, &shortestDis);
            
            if (returnValue)
            {
                reportErr(returnValue, argv[1]);
                printf("Type any to continue.");
                scanf("%s", input);
                continue;
            }
            printf("The shortest length is: %lf\n", shortestDis);
            printf("The pasted nodes are:\n");
            for (int i = 0; i < nodeCount; ++ i)
            {
                printf("%d: %ld ", i + 1, nodeList[pastNodes[i]].id);
            }
            printf("\n");
            routeShown(&boundData, linkList, nodeList, edgeList, geomList, &countList, pastNodes, nodeCount);
            printf("Type any to continue.");
            scanf("%s", input);
        }
        
        if (value == 2)
        {
            long startNode, endNode;
            double shortestDis = 0;
            int *pastNodes = NULL, nodeCount;
            char *POI = NULL;
            printf("Enter the id of first node.\n");
            scanf("%s", input);
            startNode = strtol(input, NULL, 10);
            printf("Enter the id of second node.\n");
            scanf("%s", input);
            endNode = strtol(input, NULL, 10);
            
            routeInit(&linkList, &nodeList, &edgeList, &head, &countList, 1);
            
            returnValue = dijkstra(linkList, edgeList, head, &countList, &pastNodes, &nodeCount, &nodeList, startNode,
                                   endNode, POI, &shortestDis);
            
            if (returnValue)
            {
                reportErr(returnValue, argv[1]);
                printf("Type any to continue.");
                scanf("%s", input);
                return 0;
            }
            printf("The fastest time(hour) is: %lf\n", shortestDis);
            printf("The pasted nodes are:\n");
            for (int i = 0; i < nodeCount; ++ i)
            {
                printf("%d: %ld ", i + 1, nodeList[pastNodes[i]].id);
            }
            printf("\n");
            routeShown(&boundData, linkList, nodeList, edgeList, geomList, &countList, pastNodes, nodeCount);
            printf("Type any to continue.");
            scanf("%s", input);
        }
        
        if (value == 3)
        {
            long startNode, endNode;
            double shortestDis = 0;
            int *pastNodes = NULL, nodeCount;
            char *POI = NULL;
            printf("Enter the id of first node.\n");
            scanf("%s", input);
            startNode = strtol(input, NULL, 10);
            printf("Enter the id of second node.\n");
            scanf("%s", input);
            endNode = strtol(input, NULL, 10);
            printf("Enter the POI.\n");
            scanf("%s", input);
            POI = input;
            
            routeInit(&linkList, &nodeList, &edgeList, &head, &countList, 0);
            
            returnValue = dijkstra(linkList, edgeList, head, &countList, &pastNodes, &nodeCount, &nodeList, startNode,
                                   endNode, POI, &shortestDis);
            
            if (returnValue)
            {
                reportErr(returnValue, argv[1]);
                printf("Type any to continue.");
                scanf("%s", input);
                return 0;
            }
            printf("The fastest time(hour) is: %lf\n", shortestDis);
            printf("The pasted nodes are:\n");
            for (int i = 0; i < nodeCount; ++ i)
            {
                printf("%d: %ld ", i + 1, nodeList[pastNodes[i]].id);
            }
            printf("\n");
            routeShown(&boundData, linkList, nodeList, edgeList, geomList, &countList, pastNodes, nodeCount);
            printf("Type any to continue.");
            scanf("%s", input);
        }
    }
    freeData(&linkList, &nodeList, &wayList, &geomList, &edgeList, &head);
    
    return 0;
}