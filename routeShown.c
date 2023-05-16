#include "routeShown.h"

const int WINDOW_WIDTH = 1080, WINDOW_HEIGHT = 1920;
const int RECT_WIDTH = 6, RECT_HEIGHT = 6;
const int delta = 3;

double rateX, rateY;


SDL_Rect *graphicPoints;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *tex;

void sdl_ellipse(SDL_Renderer *r, int x0, int y0, int radiusX, int radiusY)
{
    float pi = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0;
    
    const int prec = 27;
    float theta = 0;
    
    int x = (float) radiusX * cos(theta);
    int y = (float) radiusY * sin(theta);
    int x1 = x;
    int y1 = y;
    
    float step = pih / (float) prec;
    for (theta = step; theta <= pih; theta += step)
    {
        x1 = (float) radiusX * cosf(theta) + 0.5;
        y1 = (float) radiusY * sinf(theta) + 0.5;
        
        if ((x != x1) || (y != y1))
        {
            SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1);
            SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1);
            SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1);
            SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1);
        }
        x = x1;
        y = y1;
    }
    if (x != 0)
    {
        x = 0;
        SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1);
        SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1);
        SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1);
        SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1);
    }
}

void initSDL()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("routeDealing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_HEIGHT,
                              WINDOW_WIDTH, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, - 1, SDL_RENDERER_ACCELERATED);
    tex = SDL_CreateTextureFromSurface(renderer, 0);
}

void initPoint(struct bound *boundData, int nodeCount, struct node *nodeList)
{
    rateX = WINDOW_HEIGHT / (boundData->maxLon - boundData->minLon);
    rateY = WINDOW_WIDTH / (boundData->maxLat - boundData->minLat);
    
    graphicPoints = (SDL_Rect *) malloc(sizeof(SDL_Rect) * nodeCount);
    for (int i = 0; i < nodeCount; ++ i)
    {
        graphicPoints[i].x = (int) floor((nodeList[i].lon - boundData->minLon) * rateX) - delta;
        graphicPoints[i].y = (int) floor((boundData->maxLat - nodeList[i].lat) * rateY) - delta;
        graphicPoints[i].w = RECT_WIDTH;
        graphicPoints[i].h = RECT_HEIGHT;
    }
}

void closeSDL()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(tex);
    SDL_Quit();
}

void drawMap(struct bound *boundData, struct link *linkList,
             struct node *nodeList, struct edge *edgeList, struct geom *geomList, struct count *countList,
             const int *pastNode, int nodeCount)
{
    // draw background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    // draw link
    SDL_SetRenderDrawColor(renderer, 0, 139, 139, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < countList->links; ++ i)
    {
        int node1Index = findNodeIndex(nodeList, countList->nodes, linkList[i].node1),
                node2Index = findNodeIndex(nodeList, countList->nodes, linkList[i].node2);
        SDL_RenderDrawLine(renderer, graphicPoints[node1Index].x + delta, graphicPoints[node1Index].y + delta,
                           graphicPoints[node2Index].x + delta, graphicPoints[node2Index].y + delta);
    }
    
    // draw edge
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < countList->edges; ++ i)
    {
        int node1Index = findNodeIndex(nodeList, countList->nodes, linkList[edgeList[i].index].node1),
                node2Index = findNodeIndex(nodeList, countList->nodes, linkList[edgeList[i].index].node2);
        for (int size = 0; size <= 3; ++ size)
        {
            sdl_ellipse(renderer, graphicPoints[node1Index].x + delta, graphicPoints[node1Index].y + delta, size, size);
            sdl_ellipse(renderer, graphicPoints[node2Index].x + delta, graphicPoints[node2Index].y + delta, size, size);
        }
    }
    
    // draw path
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
    for (int i = 1; i < nodeCount; ++ i)
    {
        int node1Index = pastNode[i - 1],
                node2Index = pastNode[i];
        for (int size = 0; size <= 3; ++ size)
        {
            sdl_ellipse(renderer, graphicPoints[node1Index].x + delta, graphicPoints[node1Index].y + delta, size, size);
            sdl_ellipse(renderer, graphicPoints[node2Index].x + delta, graphicPoints[node2Index].y + delta, size, size);
        }
        SDL_RenderDrawLine(renderer, graphicPoints[node1Index].x + delta, graphicPoints[node1Index].y + delta,
                           graphicPoints[node2Index].x + delta, graphicPoints[node2Index].y + delta);
    }
    
    // draw geoms
    SDL_SetRenderDrawColor(renderer, 165, 42, 42, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < countList->geoms; ++ i)
    {
        for (int j = 1; j < geomList[i].size; ++ j)
        {
            int node1Index = findNodeIndex(nodeList, countList->nodes, geomList[i].nodes[j - 1]),
                    node2Index = findNodeIndex(nodeList, countList->nodes, geomList[i].nodes[j]);
            SDL_RenderDrawLine(renderer, graphicPoints[node1Index].x + delta, graphicPoints[node1Index].y + delta,
                               graphicPoints[node2Index].x + delta, graphicPoints[node2Index].y + delta);
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(60000);
}

int routeShown(struct bound *boundData, struct link *linkList, struct node *nodeList, struct edge *edgeList,
               struct geom *geomList, struct count *countList, int *pastNode, int nodeCount)
{
    initSDL();
    
    initPoint(boundData, countList->nodes, nodeList);
    
    drawMap(boundData, linkList, nodeList, edgeList, geomList, countList, pastNode, nodeCount);
    
    closeSDL();
    return EXIT_NO_ERRORS;
}

void showLink(struct link *tmpLink)
{
    printf("id: %ld\n", tmpLink->id);
    printf("node: %ld, node: %ld\n", tmpLink->node1, tmpLink->node2);
    printf("way: %ld\n", tmpLink->way);
    printf("length: %lf\n", tmpLink->length);
    printf("speedLimit: %lf(KM/H)\n", tmpLink->speedLimit);
    
    for (int i = 0; i < tmpLink->attributeCount; ++ i)
        printf("%s: %lf\n", tmpLink->attributeName[i], tmpLink->attribute[i]);
    
    printf("POI:");
    for (int i = 0; i < tmpLink->totalPOI; ++ i)
    {
        printf("%s", tmpLink->POI[i]);
        if (i < tmpLink->totalPOI - 1) printf(",");
    }
    printf(";\n");
}

void
writeFile(char *filename, struct link *linkList, struct node *nodeList, struct way *wayList, struct geom *geomList,
          struct count countList, struct bound boundData)
{
    FILE *inputFile = fopen(filename, "w");
    fprintf(inputFile, "<bounding minLat=%lf minLon=%lf maxLat=%lf maxLon=%lf /bounding>\n", boundData.minLat,
            boundData.minLon, boundData.maxLat, boundData.maxLon);
    
    for (int i = 0; i < countList.links; ++ i)
    {
        fprintf(inputFile, "<link ");
        fprintf(inputFile, "id=%ld ", linkList[i].id);
        fprintf(inputFile, "node=%ld node=%ld ", linkList[i].node1, linkList[i].node2);
        fprintf(inputFile, "way=%ld ", linkList[i].way);
        fprintf(inputFile, "length=%lf ", linkList[i].length);
        fprintf(inputFile, "SpeedLimit=%lf ", linkList[i].speedLimit);
        
        for (int j = 0; j < linkList[i].attributeCount; ++ j)
            fprintf(inputFile, "%s=%lf ", linkList[i].attributeName[j], linkList[i].attribute[j]);
        fprintf(inputFile, "POI:");
        for (int j = 0; j < linkList[i].totalPOI; ++ j)
        {
            fprintf(inputFile, "%s", linkList[i].POI[j]);
            fprintf(inputFile, ",");
        }
        fprintf(inputFile, ";/link>\n");
    }
    
    for (int i = 0; i < countList.nodes; ++ i)
    {
        fprintf(inputFile, "<node ");
        fprintf(inputFile, "id=%ld ", nodeList[i].id);
        fprintf(inputFile, "lat=%lf lon:=%lf ", nodeList[i].lat, nodeList[i].lon);
        fprintf(inputFile, "/node>\n");
    }
    
    for (int i = 0; i < countList.ways; ++ i)
    {
        fprintf(inputFile, "<ways ");

        fprintf(inputFile, "id=%ld ", wayList[i].id);
        for (int j = 0; j < wayList[i].size; ++ j)
        {
            fprintf(inputFile, "node=%ld ", wayList[i].nodes[j]);
        }

        fprintf(inputFile, "/way>\n");
    }

    for (int i = 0; i < countList.geoms; ++ i)
    {
        fprintf(inputFile, "<geom ");

        fprintf(inputFile, "id=%ld ", geomList[i].id);
        for (int j = 0; j < geomList[i].size; ++ j)
        {
            fprintf(inputFile, "node=%ld ", geomList[i].nodes[j]);
        }

        fprintf(inputFile, "/geom>\n");
    }
    
    fclose(inputFile);
}