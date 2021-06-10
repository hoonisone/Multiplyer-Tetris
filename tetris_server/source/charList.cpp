#include "charList.h"
#include <stdio.h>
#include <stdlib.h>

static int listCharEqual(Data data1, Data data2);
static int listCharCompare(Data data1, Data data2);
static void listCharPrint(Data data);
static void listCharDelete(Data data);

List * createCharList() {
	return createList(listCharEqual, listCharCompare, listCharPrint, listCharDelete);
}

int listCharEqual(Data data1, Data data2) {
	char* value1 = (char*)data1;
	char* value2 = (char*)data2;
	return (*value1 == *value2);
}
int listCharCompare(Data data1, Data data2) {
	char* value1 = (char*)data1;
	char* value2 = (char*)data2;
	return (*value1 < *value2);
}
void listCharPrint(Data data) {
	char* value = (char*)data;
	printf("%c", *value);
}
void listCharDelete(Data data) {
	free(data);
}