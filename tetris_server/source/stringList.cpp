#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stringList.h"

static int listStringEqual(Data data1, Data data2);
static int listStringCompare(Data data1, Data data2);
static void listStringPrint(Data data);
static void listStringDelete(Data data);

List* createStringList() {
	return createList(listStringEqual, listStringCompare, listStringPrint, listStringDelete);
}

int listStringEqual(Data data1, Data data2) {
	char* value1 = (char*)data1;
	char* value2 = (char*)data2;
	return strcmp(value1, value2) == 0;
}
int listStringCompare(Data data1, Data data2) {
	char* value1 = (char*)data1;
	char* value2 = (char*)data2;
	return strcmp(value1, value2) == 1;
}
void listStringPrint(Data data) {
	char* value = (char*)data;
	printf("%s", value);
}
void listStringDelete(Data data) {
	free(data);
}