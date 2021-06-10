#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "utill.h"
#include "stringList.h"

List* readFileIntoList(char* fileName) {
	List* list = createStringList();
	FILE* fp = fopen(fileName, "r");
	char line[FILE_LINE_SIZE];
	while (fgets(line, FILE_LINE_SIZE, fp) != NULL) {
		line[strlen(line) - 1] = NULL;
		list->pushBackElement(list, newString(line));
	}
	return list;
}

void writeListIntoFile(List* list, char* fileName) {
	FILE* fp = fopen(fileName, "w");
	for (int i = 0; i < list->getSize(list); i++) {
		char* line = (char*)list->getElement(list, i);
		fputs(line, fp);
		fputs("\n", fp);
	}
}
