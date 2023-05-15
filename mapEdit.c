#include "mapEdit.h"

int addLink(struct link *linkList, struct count *countList, struct link *addedLink)
{
    linkList[countList->links] = *addedLink;
    countList->links ++;
    return EXIT_NO_ERRORS;
}

int addNode(struct node *nodeList, struct count *countList, struct node *addedNode)
{
    nodeList[countList->nodes] = *addedNode;
    countList->nodes ++;
    return EXIT_NO_ERRORS;
}

int addWay(struct way *wayList, struct count *countList, struct way *addedWay)
{
    wayList[countList->ways] = *addedWay;
    countList->ways ++;
    return EXIT_NO_ERRORS;
}

int addGeom(struct geom *geomList, struct count *countList, struct geom *addedGeom)
{
    geomList[countList->geoms] = *addedGeom;
    countList->geoms ++;
    return EXIT_NO_ERRORS;
}

int editAttribute(struct link *linkList, int index)
{
    char input[maxAttNameLength];
    printf("Enter the attribute you want to edit.\n");
    scanf("%s", input);
    
    if (memcmp(input, "POI", 3) == 0)
    {
        printf("Enter the POI value you want to add.\n");
        scanf("%s", input);
        linkList[index].totalPOI += 1;
        
        for(int i=0;i< strlen(input);++i) linkList[index].POI[linkList->totalPOI - 1][i] = input[i];
        printf("%s\n", linkList[index].POI[linkList->totalPOI - 1]);
        return EXIT_NO_ERRORS;
    }
    
    if (memcmp(input, "SpeedLimit", 10) == 0)
    {
        printf("Enter the SpeedLimit you want to edit.\n");
        scanf("%s", input);
        linkList[index].speedLimit = strtod(input, NULL);
        return EXIT_NO_ERRORS;
    }
    
    for (int i = 0; i < linkList[index].attributeCount; ++ i)
    {
        int length = strlen(linkList[index].attributeName[i]) < strlen(input) ? (int) strlen(linkList[index].attributeName[i])
                                                                        : (int) strlen(input);
        if (memcmp(input, linkList[index].attributeName[i], length) == 0)
        {
            printf("Enter the %s value you want to edit.\n", linkList[index].attributeName[i]);
            scanf("%s", input);
            linkList[index].attribute[i] = strtod(input, NULL);
            return EXIT_NO_ERRORS;
        }
    }
    
    return EXIT_NOT_APPEARED_ATTRIBUTE;
}
