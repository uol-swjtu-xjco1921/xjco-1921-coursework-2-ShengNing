#include "mapRead.h"

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
    
    long *wayIndex, *geomIndex;
    wayIndex = malloc((countList->ways + 1) * sizeof(long));
    geomIndex = malloc((countList->geoms + 1) * sizeof(long));
    
    for (int i = 0; i < (countList->ways); ++ i) wayIndex[i] = (*wayList + i)->id;
    for (int i = 0; i < (countList->geoms); ++ i) geomIndex[i] = (*geomList + i)->id;
    
    sortData(linkList, nodeList, &wayIndex, &geomIndex, countList);
    
    int returnValue = detectData(linkList, nodeList, wayList, geomList, countList, &wayIndex, &geomIndex);
    if (returnValue)
    {
        free(wayIndex);
        free(geomIndex);
        return returnValue;
    }
    
    dealEdges(linkList, nodeList, &wayIndex, edgeList, head, countList);
    
    free(wayIndex);
    free(geomIndex);
    
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
    (tmpLink->POI) = malloc(0 * sizeof(char *));
    
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
                free(tmpLink);
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
                free(tmpLink);
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            if (tmpLink->node1) tmpLink->node2 = strtol(tmpStr, NULL, 10);
            else tmpLink->node1 = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "way", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
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
                free(tmpLink);
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpLink->length = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "veg", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpLink->veg = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "arch", 4) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpLink->arch = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "land", 4) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return EXIT_Bad_Data;
            }
            ++ tmpStr;
            tmpLink->land = strtod(tmpStr, NULL);
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
                    int maxPOI = 100;
                    if (strlen(poiStr) > 100)
                    {
                        free(tmpLink);
                        return EXIT_Bad_Data;
                    }
                    
                    (tmpLink->POI) = realloc(*(tmpLink->POI), (tmpLink->totalPOI + 1) * maxPOI * sizeof(char));
                    strcpy(*(tmpLink->POI + tmpLink->totalPOI), poiStr);
                    tmpLink->totalPOI += 1;
                    poiStr = strtok(NULL, ",");
                }
            }
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
                free(tmpNode);
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
                free(tmpNode);
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
                free(tmpNode);
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
                free(tmpWay);
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
                free(tmpWay);
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
                free(tmpGeom);
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
                free(tmpGeom);
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

