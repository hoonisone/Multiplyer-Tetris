#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "list.h"
#include "utill.h"

List* readFileIntoList(char* fileName) {
	List* list = listCreateList(listStringEqual, listStringCompare, listStringPrint, listStringDelete);
	FILE* fp = fopen(fileName, "r");
	char line[FILE_LINE_SIZE];
	while (fgets(line, FILE_LINE_SIZE, fp) != NULL) {
		line[strlen(line) - 1] = NULL;
		listPushBackElement(list, newString(line));
	}
	return list;
}

void writeListIntoFile(List* list, char* fileName) {
	FILE* fp = fopen(fileName, "w");
	for (int i = 0; i < listGetSize(list); i++) {
		char* line = (char*)listGetElement(list, i);
		fputs(line, fp);
		fputs("\n", fp);
	}
}
