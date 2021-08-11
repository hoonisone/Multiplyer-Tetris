#pragma once
#include <string>
#define errorPrint(message)	_errorPrint((char*)__FILE__, (char*)__func__, __LINE__, (string)message)

using namespace std;


void _errorPrint(char* fileName, char* funcName, int line, string message);
