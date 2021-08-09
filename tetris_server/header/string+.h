#pragma once
#include <vector>
#include <string>
#include "list.h"
#include "graphic.h"

#define ALIGN_LEFT		0
#define ALIGN_MIDDLE	1
#define ALIGN_RIGHT		2

using namespace std;

char* createString(char* string);
List* split(char* text, char* key);
vector<string> split(string s, string key);
void textPrintLeft(int x, int y, int w, int h, char* text);
void textPrintMiddle(int x, int y, int w, int h, char* text);
void textPrintRight(int x, int y, int w, int h, char* text);
void textPrintAlign(int x, int y, int w, int h, char* text, int align = ALIGN_MIDDLE);
