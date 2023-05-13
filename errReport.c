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
        case EXIT_Bad_Data:
            printf("Error: Exit bad data.\n");
            break;
        case EXIT_REPEAT_ID:
            printf("Error: Exit repeat id in %s.\n", filename);
            break;
        case EXIT_UNKNOWN_NODE:
            printf("Error: Exit unknown node in %s.\n", filename);
            break;
        case EXIT_UNKNOWN_WAY:
            printf("Error: Exit unknown way in %s.\n", filename);
            break;
        case EXIT_UNMATCHED_LENGTH:
            printf("Error: Exit unmatched length in %s.\n", filename);
            break;
        default:
            printf("ERROR: Unknown error.\n");
    }
}
