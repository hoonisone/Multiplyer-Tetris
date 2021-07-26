#pragma once
#include "list.h"
#include "graphic.h"

#define ALIGN_LEFT		0
#define ALIGN_MIDDLE	1
#define ALIGN_RIGHT		2

char* createString(char* string);
List* split(char* string, char* key);
void textPrintLeft(int x, int y, int w, int h, char* text);
void textPrintMiddle(int x, int y, int w, int h, char* text);
void textPrintRight(int x, int y, int w, int h, char* text);
void textPrintAlign(int x, int y, int w, int h, char* text, int align);
