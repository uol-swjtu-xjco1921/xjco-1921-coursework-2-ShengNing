#include "mapRead.h"



int readFile(char *filename, struct link **edge, int **head)
{
    FILE *inputFile = fopen(filename, "r");
    if(inputFile == NULL)
    {
        reportErr(EXIT_BAD_INPUT_FILE, filename);
        return EXIT_BAD_INPUT_FILE;
    }
    
    return EXIT_NO_ERRORS;
}