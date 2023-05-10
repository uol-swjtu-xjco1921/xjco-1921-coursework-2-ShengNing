#include "mapRead.h"

int readFile(char *filename, struct link **linkList, struct node **nodeList,
        struct way **wayList, struct geom **geomList, struct count *countList)
{
    FILE *inputFile = fopen(filename, "r");
    if(inputFile == NULL)
    {
        reportErr(EXIT_BAD_INPUT_FILE, filename);
        return EXIT_BAD_INPUT_FILE;
    }
    
    
    
    return EXIT_NO_ERRORS;
}

struct link readLink(char *inputStr, struct link **linkList)
{

}

struct node readNode(char *inputStr, struct node **nodeList)
{

}

struct way readWay(char *inputStr, struct way **wayList)
{

}

struct geom readGeom(char *input, struct geom **geomList)
{

}


void dealEdges(struct link **linkList, struct node **nodeList,
        struct way **wayList, struct edge **edgeList)
{
    // addEdge(&edgeList, &totalEdges, addedLink);
}