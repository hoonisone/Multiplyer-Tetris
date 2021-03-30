#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void ErrorHandling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}