#pragma warning(disable:4996)
#include <string.h>
#include "string+.h"
#include "stringList.h"
#include "list.h"
#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

char* createString(char* string) {
	char* token = (char*)malloc(sizeof(char) * (strlen(string) + 1));
	strcpy(token, string);
	return token;
}
List* split(char* string, char* key) {
	List* list = createStringList();
	char* copy = createString(string);
	char* ptr = strtok(copy, key);
	while (ptr != NULL) {
		list->pushBackElement(list, createString(ptr));
		ptr = strtok(NULL, key);
	}
	free(copy);
	return list;
}
vector<string> split(string s, string key) {
	int pos1 = 0, pos2;
	vector<string> tokens;
	while ((pos2 = s.find(key, pos1)) != -1) {
		tokens.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + key.size();
	}
	pos2 = s.size();
	tokens.push_back(s.substr(pos1, pos2 - pos1));
	return tokens;
}

void textPrintLeft(int x, int y, int w, int h, char* text) {
	char key[] = "\n";
	List *list = split(text, key);
	int lineNum = list->getSize(list);
	y += (h - lineNum) / 2;
	for (int i = 0; i < lineNum; i++) {
		GRAPHIC->printText(x, y + i, (char*)list->getElement(list, i));
	}
	list->deleteList(list);
}


void textPrintMiddle(int x, int y, int w, int h, char* text) {
	char key[] = "\n";
	List* list = split(text, key);
	int lineNum = list->getSize(list);
	y += (h - lineNum) / 2;
	for (int i = 0; i < lineNum; i++) {
		int lineX = x + (w*2 - strlen((char*)list->getElement(list, i)))/2;
		int lineY = y + i;
		GRAPHIC->printText(lineX, lineY, (char*)list->getElement(list, i));
	}
	list->deleteList(list);
}

void textPrintRight(int x, int y, int w, int h, char* text) {
	char key[] = "\n";
	List* list = split(text, key);
	int lineNum = list->getSize(list);
	y += (h - lineNum) / 2;
	for (int i = 0; i < lineNum; i++) {
		int lineX = x + w*2 - 1 - strlen((char*)list->getElement(list, i));
		int lineY = y + i;
		
		GRAPHIC->printText(lineX, lineY, (char*)list->getElement(list, i));
	}
	list->deleteList(list);
}

void textPrintAlign(int x, int y, int w, int h, char* text, int align) {
	if (align == ALIGN_LEFT)
		textPrintLeft(x, y, w, h, text);
	else if (align == ALIGN_MIDDLE)
		textPrintMiddle(x, y, w, h, text);
	else if (align == ALIGN_RIGHT)
		textPrintRight(x, y, w, h, text);
}

template<typename ... Args>
string string_f(const string& format, Args ... args) {
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0' 
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return string(buf.get(), buf.get() + size - 1);
}