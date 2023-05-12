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
        struct geom tmpGeom ;
        
        if (memcmp(inputStr, "<bounding", 9) == 0)
        {
            flag = readBound(inputStr, boundData);
        }
        
        if (memcmp(inputStr, "<link", 5) == 0)
        {
            readLink(inputStr, &tmpLink);
            
            *linkList = realloc(*linkList, ((*countList).links + 1) * sizeof(struct link));
            addLink(*linkList, countList, &tmpLink);
        }
        
        if (memcmp(inputStr, "<node", 5) == 0)
        {
            readNode(inputStr, &tmpNode);
            
            *nodeList = realloc(*nodeList, ((*countList).nodes + 1) * sizeof(struct node));
            addNode(*nodeList, countList, &tmpNode);
        }
        
        if (memcmp(inputStr, "<way", 4) == 0)
        {
            readWay(inputStr, &tmpWay);
            
            *wayList = realloc(*wayList, ((*countList).ways + 1) * sizeof(struct way));
            addWay(*wayList, countList, &tmpWay);
        }
        
        if (memcmp(inputStr, "<geom", 5) == 0)
        {
            readGeom(inputStr, &tmpGeom);
            
            *geomList = realloc(*geomList, ((*countList).geoms + 1) * sizeof(struct geom));
            addGeom(*geomList, countList, &tmpGeom);
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
            ++tmpStr;
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
            ++tmpStr;
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
            ++tmpStr;
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
            ++tmpStr;
            boundData->maxLon = strtod(tmpStr, NULL);
        }
        
        divStr = strtok(NULL, " ");
    }
    return EXIT_NO_ERRORS;
}

void readLink(char *inputStr, struct link *tmpLink)
{
    tmpLink = malloc(sizeof(struct link));
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
                return;
            }
            ++tmpStr;
            tmpLink->id = strtol(tmpStr, NULL, 10);
            
        }
        
        else if (memcmp(divStr, "node", 4) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return;
            }
            ++tmpStr;
            if (tmpLink->node1) tmpLink->node2 = strtol(tmpStr, NULL, 10);
            tmpLink->node1 = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "way", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return;
            }
            ++tmpStr;
            tmpLink->way = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "length", 6) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return;
            }
            ++tmpStr;
            tmpLink->length = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "veg", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return;
            }
            ++tmpStr;
            tmpLink->veg = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "arch", 4) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return;
            }
            ++tmpStr;
            tmpLink->arch = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "land", 4) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpLink);
                return;
            }
            ++tmpStr;
            tmpLink->land = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "POI", 4) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr != NULL)
            {
                ++tmpStr;
                
                long pos = strstr(tmpStr, ";") - tmpStr;
                char *poiStr = NULL;
                strncpy(poiStr, tmpStr, pos);
                
                poiStr = strtok(poiStr, ",");
                
                while (poiStr != NULL)
                {
                    *(tmpLink->POI) = realloc(*(tmpLink->POI), tmpLink->totalPOI + 1 * sizeof(char *));
                    tmpLink->POI[tmpLink->totalPOI] = poiStr;
                    tmpLink->totalPOI += 1;
                    poiStr = strtok(NULL, ",");
                }
            }
        }
        
        divStr = strtok(NULL, " ");
    }
}

void readNode(char *inputStr, struct node *tmpNode)
{
    tmpNode = malloc(sizeof(struct node));
    
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
                return;
            }
            ++tmpStr;
            tmpNode->id = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "lat", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpNode);
                return;
            }
            ++tmpStr;
            tmpNode->lat = strtod(tmpStr, NULL);
        }
        
        else if (memcmp(divStr, "lon", 3) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpNode);
                return;
            }
            ++tmpStr;
            tmpNode->lon = strtod(tmpStr, NULL);
        }
        
        divStr = strtok(NULL, " ");
    }
}

void readWay(char *inputStr, struct way *tmpWay)
{
    tmpWay = malloc(sizeof(struct way));
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
                return;
            }
            ++tmpStr;
            tmpWay->id = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "node", 2) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpWay);
                return;
            }
            ++tmpStr;
            tmpWay->nodes = realloc(tmpWay->nodes, (tmpWay->size + 1) * sizeof(long));
            tmpWay->nodes[tmpWay->size] = strtol(tmpStr, NULL, 10);
            tmpWay->size += 1;
        }
        
        divStr = strtok(NULL, " ");
    }
}

void readGeom(char *inputStr, struct geom *tmpGeom)
{
    tmpGeom = malloc(sizeof(struct geom));
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
                return;
            }
            ++tmpStr;
            tmpGeom->id = strtol(tmpStr, NULL, 10);
        }
        
        else if (memcmp(divStr, "node", 2) == 0)
        {
            char *tmpStr;
            tmpStr = memchr(divStr, '=', strlen(divStr));
            if (tmpStr == NULL)
            {
                free(tmpGeom);
                return;
            }
            ++tmpStr;
            tmpGeom->nodes = realloc(tmpGeom->nodes, (tmpGeom->size + 1) * sizeof(long));
            tmpGeom->nodes[tmpGeom->size] = strtol(tmpStr, NULL, 10);
            tmpGeom->size += 1;
        }
        
        divStr = strtok(NULL, " ");
    }
}