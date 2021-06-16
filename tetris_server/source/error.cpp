#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void ErrorHandling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void _errorPrint(char* fileName, char* funcName, int line, char* message) {
    printf("Error:\n");
    printf("\tFile: %s\n", fileName);
    printf("\tFunc: %s\n", funcName);
    printf("\tLine: %d\n", line);
    printf("\tMessage: %s\n", message);
    exit(-1);
}