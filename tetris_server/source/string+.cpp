#pragma warning(disable:4996)
#include <string.h>
#include "string+.h"
#include "stringList.h"
#include "list.h"
#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>

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
		int lineX = x + w - strlen((char*)list->getElement(list, i))/2;
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
		int lineX = x + w - strlen((char*)list->getElement(list, i));
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
