#pragma once
#include <iostream>
#include <string>
#define errorPrint(message)	_errorPrint((char*)__FILE__, (char*)__func__, __LINE__, (std::string)message)

void _errorPrint(char* fileName, char* funcName, int line, std::string message) {
    printf("Error:\n");
    printf("\tFile: %s\n", fileName);
    printf("\tFunc: %s\n", funcName);
    printf("\tLine: %d\n", line);
    std::cout << "\tMessage: " << message << "\n";
    exit(-1);
}