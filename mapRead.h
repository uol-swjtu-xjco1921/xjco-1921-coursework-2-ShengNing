#include <stdio.h>
#include "errReport.h"

struct link
{
    int id;
    int to;
    int nxt;
    int way;
    double length, veg, arch, land;
    char *POI;
};

struct node
{
    int id;
    double lat, lon;
};


int readFile(char *filename, struct link **edge, int **head);