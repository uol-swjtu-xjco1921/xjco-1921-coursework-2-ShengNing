
#include "errReport.h"
#include "mapEdit.h"
#include "routeInit.h"
#include "routeSearch.h"
#include "routeShown.h"

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        reportErr(EXIT_WRONG_ARG_COUNT, argv[0]);
        return EXIT_WRONG_ARG_COUNT;
    }
    
    struct link *linkList;
    struct node *nodeList;
    struct way *wayList;
    struct geom *geomList;
    struct count countList;
    int *head;
    int returnValue = readFile(argv[1], &linkList, &nodeList,
                               &wayList, &geomList, &countList);
    if(returnValue) return returnValue;
    
    return 0;
}