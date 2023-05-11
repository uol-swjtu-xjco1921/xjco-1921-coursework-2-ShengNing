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
        switch (inputStr[1])
        {
            case 'l':
                readLink(inputStr, linkList, countList);
                break;
            case 'n':
                readNode(inputStr, nodeList, countList);
                break;
            case 'w':
                readWay(inputStr, wayList, countList);
                break;
            case 'g':
                readGeom(inputStr, geomList, countList);
                break;
            default:
                reportErr(EXIT_Bad_Data, filename),
                        flag = EXIT_Bad_Data;
                break;
        }
        if (flag != EXIT_NO_ERRORS)
        {
            fclose(inputFile);
            free(inputStr);
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

struct link readLink(char *inputStr, struct link **linkList, struct count *countList)
{

}

struct node readNode(char *inputStr, struct node **nodeList, struct count *countList)
{

}

struct way readWay(char *inputStr, struct way **wayList, struct count *countList)
{

}

struct geom readGeom(char *input, struct geom **geomList, struct count *countList)
{

}


void dealEdges(struct link **linkList, struct node **nodeList,
               struct way **wayList, struct edge **edgeList, int **head, struct count *countList)
{
    // addEdge(&edgeList, &totalEdges, addedLink);
}