#include <stdio.h>
#include <SDL2/SDL.h>
#include "dataStructure.h"
#include "errReport.h"
#include "routeInit.h"

void sdl_ellipse(SDL_Renderer *r, int x0, int y0, int radiusX, int radiusY);

void initSDL();

void initPoint(struct bound *boundList, int nodeCount, struct node *nodeList);

void closeSDL();

void drawMap(struct bound *boundList, struct link *linkList,
             struct node *nodeList, struct edge *edgeList, struct geom *geomList, struct count *countList,
             const int *pastNode, int nodeCount);

int routeShown(struct bound *boundList, struct link *linkList, struct node *nodeList, struct edge *edgeList,
               struct geom *geomList, struct count *countList, int *pastNode, int nodeCount);

void showLink(struct link *tmpLink);

void
writeFile(char *filename, struct link *linkList, struct node *nodeList, struct way *wayList, struct geom *geomList,
          struct count countList, struct bound boundData);