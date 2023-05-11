
#include "errReport.h"
#include "mapEdit.h"
#include "routeInit.h"
#include "routeSearch.h"
#include "routeShown.h"

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
        return returnValue;
    }
    
    return 0;
}