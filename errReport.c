#include "errReport.h"

void reportErr(int value, char *filename)
{
    switch (value)
    {
        case EXIT_WRONG_ARG_COUNT:
            printf();
            break;
        case EXIT_BAD_INPUT_FILE:
            printf();
            break;
        case EXIT_BAD_Comment_Line:
            printf();
            break;
        case EXIT_Bad_Data:
            printf();
            break;
        case EXIT_BAD_OUTPUT_FILE:
            printf();
            break;
        default:
            printf("ERROR: Unknown error.\n");
    }
    return;
}
