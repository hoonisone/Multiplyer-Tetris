#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "error.h"

void _errorPrint(char* fileName, char* funcName, int line, string message) {
    printf("Error:\n");
    printf("\tFile: %s\n", fileName);
    printf("\tFunc: %s\n", funcName);
    printf("\tLine: %d\n", line);
    cout << "\tMessage: " << message << "\n";
    exit(-1);
}