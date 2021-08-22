#pragma once
#include <string>
#define errorPrint(message)	_errorPrint((char*)__FILE__, (char*)__func__, __LINE__, (std::string)message)

void _errorPrint(char* fileName, char* funcName, int line, std::string message);
