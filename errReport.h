#include <stdio.h>

// ERROR
// Program given wrong # of arguments
#define EXIT_WRONG_ARG_COUNT 0

// Program fails to open file
#define EXIT_BAD_INPUT_FILE 1

// Program failed on comment line
#define EXIT_BAD_Comment_Line 2

// Reading in data failed
#define EXIT_Bad_Data 3

// Writing out data failed
#define EXIT_BAD_OUTPUT_FILE 4

#define EXIT_Extinct_Error 100

// Successful
#define EXIT_NO_ERRORS 0

void reportErr(int value, char *filename);
