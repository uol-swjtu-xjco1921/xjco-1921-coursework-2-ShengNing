#include "mapRead.h"

long *wayIndexUnion, *geomIndexUnion;

int readFile(char *filename, struct link **linkList, struct node **nodeList, struct way **wayList,
             struct geom **geomList, struct edge **edgeList, int **head, struct count *countList,
             struct bound *boundData)
{
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL)
    {
        return EXIT_BAD_INPUT_FILE;
    }
    
    initData(linkList, nodeList, wayList, geomList, edgeList, head, countList);
    
    int maxLength = 700;
    char *inputStr;
    inputStr = malloc((maxLength + 1) * sizeof(char));
    
    while (fgets(inputStr, maxLength, inputFile) != NULL)
    {
        int flag = EXIT_NO_ERRORS;
        struct link *tmpLink = malloc(sizeof(struct link));
        struct node *tmpNode = malloc(sizeof(struct node));
        struct way *tmpWay = malloc(sizeof(struct way));
        struct geom *tmpGeom = malloc(sizeof(struct geom));
        
        if (memcmp(inputStr, "<bounding", 9) == 0)
        {
            flag = readBound(inputStr, boundData);
        }
        
        if (memcmp(inputStr, "<link", 5) == 0)
        {
            flag = readLink(inputStr, tmpLink);
            if (! flag)
            {
                *linkList = realloc(*linkList, ((*countList).links + 1) * sizeof(struct link));
                addLink(*linkList, countList, tmpLink);
            }
        }
        
        if (memcmp(inputStr, "<node", 5) == 0)
        {
            flag = readNode(inputStr, tmpNode);
            if (! flag)
            {
                *nodeList = realloc(*nodeList, ((*countList).nodes + 1) * sizeof(struct node));
                addNode(*nodeList, countList, tmpNode);
            }
        }
        
        if (memcmp(inputStr, "<way", 4) == 0)
        {
            flag = readWay(inputStr, tmpWay);
            if (! flag)
            {
                *wayList = realloc(*wayList, ((*countList).ways + 1) * sizeof(struct way));
                addWay(*wayList, countList, tmpWay);
            }
        }
        
        if (memcmp(inputStr, "<geom", 5) == 0)
        {
            flag = readGeom(inputStr, tmpGeom);
            if (! flag)
            {
                *geomList = realloc(*geomList, ((*countList).geoms + 1) * sizeof(struct geom));
                addGeom(*geomList, countList, tmpGeom);
            }
        }
        
        free(tmpLink);
        free(tmpNode);
        free(tmpWay);
        free(tmpGeom);
        if (flag != EXIT_NO_ERRORS)
        {
            fclose(inputFile);
            free(inputStr);
            return flag;
        }
        
    }
    free(inputStr);
    
    wayIndexUnion = malloc((countList->ways + 1) * sizeof(long));
    geomIndexUnion = malloc((countList->geoms + 1) * sizeof(long));
    
    for (int i = 0; i < (countList->ways); ++ i) wayIndexUnion[i] = (*wayList + i)->id;
    for (int i = 0; i < (countList->geoms); ++ i) geomIndexUnion[i] = (*geomList + i)->id;
    
    sortData(linkList, nodeList, &wayIndexUnion, &geomIndexUnion, countList);
    
    int returnValue = detectData(boundData, linkList, nodeList, wayList, geomList, countList, &wayIndexUnion, &geomIndexUnion);
    if (returnValue)
    {
        free(wayIndexUnion);
        free(geomIndexUnion);
        return returnValue;
    }
    
    dealEdges(linkList, nodeList, &wayIndexUnion, edgeList, head, countList);
    initSpeed(linkList, countList);
    
    free(wayIndexUnion);
    free(geomIndexUnion);
    
    return EXIT_NO_ERRORS;
}

void freeData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head)
{
    free(*linkList);
    free(*nodeList);
    free(*wayList);
    free(*geomList);
    free(*edgeList);
    free(*head);
}

void initData(struct link **linkList, struct node **nodeList, struct way **wayList,
              struct geom **geomList, struct edge **edgeList, int **head, struct count *countList)
{
    countList->links = 0;
    countList->nodes = 0;
    countList->ways = 0;
    countList->geoms = 0;
    countList->edges = 0;
    
    
    *linkList = malloc(0 * sizeof(struct link));
    *nodeList = malloc(0 * sizeof(struct node));
    *wayList = malloc(0 * sizeof(struct way));
    *geomList = malloc(0 * sizeof(struct geom));
    *edgeList = malloc(0 * sizeof(struct edge));
    *head = malloc(0 * sizeof(int));
    
}

int readBound(char *inputStr, struct bound *boundData)
{
    char *divStr = NULL;
    divStr = strtok(inputStr, " ");
    
    while (divStr != NULL)
    {
        
        if (memcmp(divStr, "minLat", 6) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            boundData->minLat = strtod(tmpStr, NULL);
        }
        
        if (memcmp(divStr, "maxLat", 6) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            boundData->maxLat = strtod(tmpStr, NULL);
        }
        
        if (memcmp(divStr, "minLon", 6) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            boundData->minLon = strtod(tmpStr, NULL);
        }
        
        if (memcmp(divStr, "maxLon", 6) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            boundData->maxLon = strtod(tmpStr, NULL);
        }
        
        divStr = strtok(NULL, " ");
    }
    return EXIT_NO_ERRORS;
}

int readLink(char *inputStr, struct link *tmpLink)
{
    tmpLink->totalPOI = 0;
    tmpLink->attributeCount = 0;
    //(tmpLink->POI) = malloc(0 * sizeof(char *));
    
    char *divStr;
    divStr = strtok(inputStr, " ");
    
    while (divStr != NULL)
    {
        
        if (memcmp(divStr, "id", 2) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpLink->id = strtol(tmpStr, NULL, 10);
            
        }
        
        else if (memcmp(divStr, "node", 4) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            if (tmpLink->node1 < 10000000000 && tmpLink->node1 > - 10000000000)
                tmpLink->node2 = strtol(tmpStr, NULL, 10);
            else tmpLink->node1 = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "way", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpLink->way = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "length", 6) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpLink->length = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "POI", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr != NULL)
            {
                ++ tmpStr;
                char *poiStr;
                poiStr = strtok(tmpStr, ",");
                
                while (poiStr != NULL)
                {
                    if (poiStr[0] == ';') break;
                    if (strlen(poiStr) > 100)
                    {
                        return EXIT_Bad_Data;
                    }
                    
                    strcpy(*(tmpLink->POI + tmpLink->totalPOI), poiStr);
                    tmpLink->totalPOI += 1;
                    poiStr = strtok(NULL, ",");
                }
            }
        }
        
        else if (memcmp(divStr, "<link", 5) != 0)
        {
            ++ tmpLink->attributeCount;
            if(tmpLink->attributeCount>15)
                return EXIT_ATTRIBUTES_LIMIT;
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                printf("%s\n", divStr);
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            for (int i = 0; i < strlen(divStr) - strlen((tmpStr)) - 1; ++ i)
                tmpLink->attributeName[tmpLink->attributeCount - 1][i] = divStr[i];
            tmpLink->attribute[tmpLink->attributeCount - 1] = strtod(tmpStr, NULL);
        }
        
        divStr = strtok(NULL, " ");
    }
    return EXIT_NO_ERRORS;
}

int readNode(char *inputStr, struct node *tmpNode)
{
    
    char *divStr = NULL;
    divStr = strtok(inputStr, " ");
    
    while (divStr != NULL)
    {
        
        if (memcmp(divStr, "id", 2) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpNode->id = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "lat", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpNode->lat = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "lon", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpNode->lon = strtod(tmpStr, NULL);
        }
        
        divStr = strtok(NULL, " ");
    }
    return EXIT_NO_ERRORS;
}

int readWay(char *inputStr, struct way *tmpWay)
{
    tmpWay->nodes = malloc(0 * sizeof(long));
    tmpWay->size = 0;
    
    char *divStr = NULL;
    divStr = strtok(inputStr, " ");
    
    while (divStr != NULL)
    {
        
        if (memcmp(divStr, "id", 2) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpWay->id = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "node", 2) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpWay->nodes = realloc(tmpWay->nodes, (tmpWay->size + 1) * sizeof(long));
            *(tmpWay->nodes + tmpWay->size) = strtol(tmpStr, NULL, 10);
            tmpWay->size += 1;
        }
        
        divStr = strtok(NULL, " ");
    }
    return EXIT_NO_ERRORS;
}

int readGeom(char *inputStr, struct geom *tmpGeom)
{
    tmpGeom->nodes = malloc(0 * sizeof(long));
    tmpGeom->size = 0;
    
    char *divStr = NULL;
    divStr = strtok(inputStr, " ");
    
    while (divStr != NULL)
    {
        
        if (memcmp(divStr, "id", 2) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpGeom->id = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "node", 2) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpGeom->nodes = realloc(tmpGeom->nodes, (tmpGeom->size + 1) * sizeof(long));
            tmpGeom->nodes[tmpGeom->size] = strtol(tmpStr, NULL, 10);
            tmpGeom->size += 1;
        }
        
        divStr = strtok(NULL, " ");
    }
    return EXIT_NO_ERRORS;
}

int wayPending(struct way **wayList, struct count *countList,long nodeId, long linkId)
{
    int wayNumber = findWayOrGeomIndex(wayIndexUnion, countList->ways, linkId);
    if(wayNumber == -1) return -1;
    wayList[wayNumber]->nodes = realloc(wayList[wayNumber]->nodes, (wayList[wayNumber]->size + 1) * sizeof(long));
    *(wayList[wayNumber]->nodes + wayList[wayNumber]->size) = nodeId;
    wayList[wayNumber]->size += 1;
    return 0;
}
