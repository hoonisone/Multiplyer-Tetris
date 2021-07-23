#pragma warning(disable:4996)
#include <string.h>
#include "string+.h"
#include "stringList.h"
#include "list.h"
#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>

List* split(char* string, char* key) {
	List* list = createStringList();
	char* copy = (char*)malloc(sizeof(char) * strlen(string)+1);
	memcpy(copy, string, strlen(string));
	char* ptr = strtok(copy, key);
	char* temp = ptr;
	printf("%s\n", temp);
	while (ptr != NULL) {
		list->pushBackElement(list, ptr);		
		printf("%s\n", (char*)list->getElement(list, 0));
		printf("%s\n", temp);
		ptr = strtok(NULL, key);

		//printf("address: %p\n", ptr);
	}
	free(copy);
	return list;
}

void textPrintLeft(int x, int y, int w, int h, char* text) {
	char key[] = "\n";
	List *list = split(text, key);
	int lineNum = list->getSize(list);
	y += (h - lineNum) / 2;
	printf("%s", (char*)list->getElement(list, 0));
	for (int i = 0; i < lineNum; i++) {
		GRAPHIC->printText(x, y + i, (char*)list->getElement(list, i));
	}
	list->deleteList(list);
}