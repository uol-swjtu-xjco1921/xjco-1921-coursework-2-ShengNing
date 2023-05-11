#include "mapRead.h"

int readFile(char *filename, struct link **linkList, struct node **nodeList, struct way **wayList,
             struct geom **geomList, struct edge **edgeList, int **head, struct count *countList,
             struct bound *boundData)
{
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL)
    {
        reportErr(EXIT_BAD_INPUT_FILE, filename);
        return EXIT_BAD_INPUT_FILE;
    }
    
    initData(linkList, nodeList, wayList, geomList, edgeList, head, countList);
    
    int maxLength = 700;
    char *inputStr;
    inputStr = malloc((maxLength + 1) * sizeof(char));
    
    while (fgets(inputStr, maxLength, inputFile) != NULL)
    {
        int flag = EXIT_NO_ERRORS;
        struct link tmpLink;
        struct node tmpNode;
        struct way tmpWay;
        struct geom tmpGeom;
        
        switch (inputStr[1])
        {
            case 'l': // Link
                tmpLink = readLink(inputStr),
                        flag = addLink(linkList, countList, &tmpLink);
                break;
            case 'n': // Node
                tmpNode = readNode(inputStr),
                        flag = addNode(nodeList, countList, &tmpNode);
                break;
            case 'w': // Way
                tmpWay = readWay(inputStr),
                        flag = addWay(wayList, countList, &tmpWay);
                break;
            case 'g': // Geom
                tmpGeom = readGeom(inputStr),
                        flag = addGeom(geomList, countList, &tmpGeom);
                break;
            default: // Unknown label
                reportErr(EXIT_Bad_Data, filename),
                        flag = EXIT_Bad_Data;
                break;
        }
        if (flag != EXIT_NO_ERRORS)
        {
            fclose(inputFile);
            free(inputStr);
            reportErr(flag, filename);
            return flag;
        }
        
    }
    
    dealEdges(linkList, nodeList, wayList, edgeList, head, countList);
    
    free(inputStr);
    return EXIT_NO_ERRORS;
}

void freeData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head)
{
    free(linkList);
    free(nodeList);
    free(wayList);
    free(geomList);
    free(edgeList);
    free(head);
}

void initData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head, struct count *countList)
{
    countList -> links = 0;
    countList -> nodes = 0;
    countList -> ways = 0;
    countList -> geoms = 0;
    countList -> edges = 0;
    
    
    *linkList = malloc(0 * sizeof(struct link));
    *nodeList = malloc(0 * sizeof(struct node));
    *wayList = malloc(0 * sizeof(struct way));
    *geomList = malloc(0 * sizeof(struct geom));
    *edgeList = malloc(0 * sizeof(struct edge));
    *head = malloc(0 * sizeof(int));
    
}

struct link readLink(char *inputStr)
{
    struct link *tmpLink = NULL, *nullLink = NULL;
    char *divStr = NULL;
    divStr = strtok(inputStr, " ");
    
    while (divStr != NULL)
    {
        char *tmpStr = NULL;
        tmpStr = strtok(divStr, "=");
        
        if (strcmp(tmpStr, "link") == 0) {}
        
        else if (strcmp(tmpStr, "id") == 0)
        {
            tmpStr = strtok(NULL, "=");
            if (tmpStr == NULL) return *nullLink;
            tmpLink -> id = (int) strtol(tmpStr, NULL, 10);
        }
        
        else if (strcmp(tmpStr, "node") == 0)
        {
            tmpStr = strtok(NULL, "=");
            if (tmpStr == NULL) return *nullLink;
            if (tmpLink -> node1) tmpLink -> node2 = (int) strtol(tmpStr, NULL, 10);
            tmpLink -> node1 = (int) strtol(tmpStr, NULL, 10);
        }
        
        else if (strcmp(tmpStr, "way") == 0)
        {
            tmpStr = strtok(NULL, "=");
            if (tmpStr == NULL) return *nullLink;
            tmpLink -> way = (int) strtol(tmpStr, NULL, 10);
        }
        
        else if (strcmp(tmpStr, "length") == 0)
        {
            tmpStr = strtok(NULL, "=");
            if (tmpStr == NULL) return *nullLink;
            tmpLink -> length = strtod(tmpStr, NULL);
        }
        
        else if (strcmp(tmpStr, "veg") == 0)
        {
            tmpStr = strtok(NULL, "=");
            if (tmpStr == NULL) return *nullLink;
            tmpLink -> veg = strtod(tmpStr, NULL);
        }
        
        else if (strcmp(tmpStr, "arch") == 0)
        {
            tmpStr = strtok(NULL, "=");
            if (tmpStr == NULL) return *nullLink;
            tmpLink -> arch = strtod(tmpStr, NULL);
        }
        
        else if (strcmp(tmpStr, "land") == 0)
        {
            tmpStr = strtok(NULL, "=");
            if (tmpStr == NULL) return *nullLink;
            tmpLink -> land = strtod(tmpStr, NULL);
        }
        
        else if (strcmp(tmpStr, "POI") == 0)
        {
            tmpStr = strtok(NULL, "=");
            if (tmpStr == NULL) return *nullLink;
            tmpLink -> POI = tmpStr;
        }
        
        divStr = strtok(NULL, " ");
    }
    return *tmpLink;
}

struct node readNode(char *inputStr)
{
    struct node *tmpNode = NULL;
    
    return *tmpNode;
}

struct way readWay(char *inputStr)
{
    struct way *tmpWay = NULL;
    
    return *tmpWay;
}

struct geom readGeom(char *input)
{
    struct geom *tmpGeom = NULL;
    
    return *tmpGeom;
}


void dealEdges(struct link **linkList, struct node **nodeList,
               struct way **wayList, struct edge **edgeList, int **head, struct count *countList)
{
    // addEdge(&edgeList, &totalEdges, addedLink);
}