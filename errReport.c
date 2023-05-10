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
        default:
            printf("ERROR: Unknown error.\n");
    }
    return;
}
