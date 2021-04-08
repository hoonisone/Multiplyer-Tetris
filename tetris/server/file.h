#pragma once
#include <stdio.h>
#include <string.h>
#include "list.h"
#define FILE_LINE_SIZE 1024

List* readFileIntoList(char* fileName);
void writeListIntoFile(List* list, char* fileName);