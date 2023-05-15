#include "errReport.h"

void reportErr(int value, char *filename)
{
    switch (value)
    {
        case EXIT_WRONG_ARG_COUNT:
            printf("Usage: %s filepath.\n", filename);
            break;
        case EXIT_BAD_INPUT_FILE:
            printf("Error: Filed to find input file.\n");
            break;
        case EXIT_TOO_LONG_POI:
            printf("Error: Exit too long POI, please enter the POI that length under 100.\n");
            break;
        case EXIT_TOO_LONG_ATT:
            printf("Error: Exit too long attribute name, please enter the attribute name that length under 15.\n");
            break;
        case EXIT_BAD_BOUNDING:
            printf("Error: The bounding is read file is paradoxically.\n");
            break;
        case EXIT_REPEAT_ID:
            printf("Error: Exit repeat id.\n");
            break;
        case EXIT_UNKNOWN_NODE:
            printf("Error: Exit unknown node.\n");
            break;
        case EXIT_UNKNOWN_LINK:
            printf("Error: Exit unknown link.\n");
            break;
        case EXIT_Bad_Data:
            printf("Error: Exit bad data.\n");
            break;
        case EXIT_UNAPPROACHABLE_NODES_PAIR:
            printf("Error: Exit nodes pair could not approachable.\n");
            break;
        default:
            printf("ERROR: Unknown error.\n");
    }
}
