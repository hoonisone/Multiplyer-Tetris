#pragma once

#define errorPrint(message)	_errorPrint((char*)__FILE__, (char*)__func__, __LINE__, (char*)message)

void ErrorHandling(char* message);

void _errorPrint(char* fileName, char* funcName, int line, char* message);
