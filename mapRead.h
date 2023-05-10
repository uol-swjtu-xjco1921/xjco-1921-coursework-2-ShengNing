#include <stdio.h>

struct link
{
    int id;
    int to;
    int nxt;
    int way;
    double length, veg, arch, land;
    char *POI;
};

void readFile(char *filename, struct link **edge, int *head);