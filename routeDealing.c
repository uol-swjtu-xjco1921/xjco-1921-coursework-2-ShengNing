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
        char input[100];
        long value = - 1;
        while (value > 3 || value < 0)
        {
            system("clear");
            printf("Enter the number to select the function.\n");
            printf("1. Query the path between two points.\n");
            printf("2. Edit the map.\n");
            printf("3. Rewrite the map.\n");
            printf("0. Exit.\n");
            scanf("%s", input);
            value = strtol(input, NULL, 10);
        }
        if (value == 0)
        {
            value = - 1;
            while (value > 1 || value < 0)
            {
                system("clear");
                printf("Exit?\n");
                printf("0. Back.\n");
                printf("1. Exit.\n");
                scanf("%s", input);
                value = strtol(input, NULL, 10);
            }
            if (value == 1) break;
            else continue;
        }
        if (value == 1)
        {
            long startNode, endNode;
            double shortestDis = 0;
            int *pastNodes = NULL, nodeCount = 0;
            char *POI = NULL;
            system("clear");
            
            printf("Enter the id of first node.\n");
            scanf("%s", input);
            startNode = strtol(input, NULL, 10);
            
            printf("Enter the id of second node.\n");
            scanf("%s", input);
            endNode = strtol(input, NULL, 10);
            int isSpeed = - 1;
            while (isSpeed > 2 || isSpeed < 0)
            {
                system("clear");
                printf("Query the shortest path or fastest path?\n");
                printf("1.Shortest path\n");
                printf("2.Fastest path.\n");
                scanf("%s", input);
                isSpeed = (int) strtol(input, NULL, 10);
            }
            
            int opt = - 1;
            while (opt > 2 || opt < 0)
            {
                system("clear");
                printf("Whether pass assigned POI?\n");
                printf("1. Yes.\n");
                printf("2. NO.\n");
                scanf("%s", input);
                opt = (int) strtol(input, NULL, 10);
            }
            if (opt == 1)
            {
                printf("Enter the POI.\n");
                scanf("%s", input);
                POI = input;
            }
            
            
            isSpeed = isSpeed == 2;
            routeInit(&linkList, &nodeList, &edgeList, &head, &countList, isSpeed);
            
            returnValue = dijkstra(linkList, edgeList, head, &countList, &pastNodes, &nodeCount, &nodeList, startNode,
                                   endNode, POI, &shortestDis);
            system("clear");
            if (returnValue)
            {
                reportErr(returnValue, "");
                printf("Type any to continue.");
                scanf("%s", input);
                continue;
            }
            if (! isSpeed)
                printf("The shortest length is: %lf\n", shortestDis);
            else
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
        
        if (value == 2)
        {
            int isAdd = - 1;
            while (isAdd > 2 || isAdd < 0)
            {
                system("clear");
                printf("Edit the map.\n");
                printf("1. Edit the route attribute.\n");
                printf("2. Add a route attribute.\n");
                printf("0. Back.\n");
                scanf("%s", input);
                isAdd = (int) strtol(input, NULL, 10);
            }
            
            if (isAdd == 2)
            {
                system("clear");
                struct link *tmpLink = malloc(sizeof(struct link));
                printf("Enter the id of link.\n");
                scanf("%s", input);
                tmpLink->id = strtol(input, NULL, 10);
                
                printf("Enter the first node of link.\n");
                scanf("%s", input);
                tmpLink->node1 = strtol(input, NULL, 10);
                
                printf("Enter the second node of link.\n");
                scanf("%s", input);
                tmpLink->node2 = strtol(input, NULL, 10);
                
                printf("Enter the speedLimit of link.\n");
                scanf("%s", input);
                tmpLink->speedLimit = strtod(input, NULL);
                
                printf("Enter the way of link.\n");
                scanf("%s", input);
                tmpLink->way = strtol(input, NULL, 10);
                
                printf("Enter the length of link.\n");
                scanf("%s", input);
                tmpLink->length = strtod(input, NULL);
                
                while(tmpLink->length<=0)
                {
                    printf("The length of link should > 0.\n");
                    scanf("%s", input);
                    tmpLink->length = strtod(input, NULL);
                }
                
                printf("Enter the numbers of attributes.\n");
                scanf("%s", input);
                tmpLink->attributeCount = (int) strtol(input, NULL, 10);
                
                for (int i = 0; i < tmpLink->attributeCount; ++ i)
                {
                    printf("Enter the name of attribute.\n");
                    scanf("%s", input);
                    if (strlen(input) >= maxAttNameLength)
                    {
                        reportErr(EXIT_TOO_LONG_ATT, "");
                        printf("Please enter again.\n");
                        i --;
                        continue;
                    }
                    strcpy(tmpLink->attributeName[i], input);
                    printf("Enter the value of attribute.\n");
                    scanf("%s", input);
                    tmpLink->attribute[i] = strtod(input, NULL);
                }
                
                printf("Enter the numbers of POI.\n");
                scanf("%s", input);
                tmpLink->totalPOI = (int) strtol(input, NULL, 10);
                
                for (int i = 0; i < tmpLink->totalPOI; ++ i)
                {
                    printf("Enter the NO.%d POI.\n", i + 1);
                    scanf("%s", input);
                    if (strlen(input) >= maxPOILength)
                    {
                        reportErr(EXIT_TOO_LONG_POI, "");
                        printf("Please enter again.\n");
                        i --;
                        continue;
                    }
                    strcpy(tmpLink->POI[i], input);
                }
                
                
                returnValue = checkLink(&nodeList, &countList, *tmpLink);
                if (returnValue)
                {
                    reportErr(returnValue, "");
                    printf("Type any to continue.");
                    scanf("%s", input);
                    continue;
                }
                
                linkList = realloc(linkList, (countList.links + 1) * sizeof(struct link));
                addLink(linkList, &countList, tmpLink);
                qsort(linkList, countList.links, sizeof(linkList[0]), cmpLink);
                
                int tmpValue = 0;
                wayPending(wayList, &countList, tmpLink->node1, tmpLink->way);
                tmpValue = wayPending(wayList, &countList, tmpLink->node2, tmpLink->way);
                
                if (tmpValue == 0)
                {
                    int linkNumber = findLinkIndex(linkList, countList.links, tmpLink->id);
                    
                    edgeList = realloc(edgeList, (countList.edges + 2) * sizeof(struct edge));
                    addEdge(linkNumber, edgeList, &nodeList, head, &countList, tmpLink);
                    countList.edges += 2;
                    
                }
                
                system("clear");
                printf("-------------Finished-------------\n");
    
                printf("The link:\n");
                showLink(tmpLink);
                printf("Type any to continue.");
                scanf("%s", input);
            }
            
            else if (isAdd == 1)
            {
                system("clear");
                printf("Enter the id of link.\n");
                scanf("%s", input);
                long linkId = strtol(input, NULL, 10);
                
                int linkNumber = findLinkIndex(linkList, countList.links, linkId);
                if (linkNumber == - 1)
                {
                    reportErr(EXIT_UNKNOWN_LINK, "");
                    printf("Type any to continue.");
                    scanf("%s", input);
                    continue;
                }
                system("clear");
                printf("The link:\n");
                showLink(&linkList[linkNumber]);
                
                returnValue = editAttribute(linkList, linkNumber);
                if (returnValue)
                {
                    reportErr(returnValue, "");
                    printf("Type any to continue.");
                    scanf("%s", input);
                    continue;
                }
                
                system("clear");
                printf("-------------Finished-------------\n");
                
                printf("Edited link:\n");
                showLink(&linkList[linkNumber]);
                printf("%s\n", linkList[linkNumber].POI[0]);
                printf("Type any to continue.");
                scanf("%s", input);
            }
        }
        
        if (value == 3)
        {
            writeFile(argv[1], linkList, nodeList, wayList, geomList, countList, boundData);
            
            printf("-------------Finished-------------\n");
            
            printf("Type any to continue.");
            scanf("%s", input);
        }
    }
    freeData(&linkList, &nodeList, &wayList, &geomList, &edgeList, &head);
    
    return 0;
}