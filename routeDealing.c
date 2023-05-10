
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
    
    struct link *edge;
    int *head;
    int returnValue = readFile(argv[1], &edge, &head);
    if(returnValue) return returnValue;
    
    return 0;
}