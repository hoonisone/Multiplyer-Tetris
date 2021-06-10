#include "intList.h"
#include <stdio.h>
#include <stdlib.h>

static int listIntEqual(Data data1, Data data2);
static int listIntCompare(Data data1, Data data2);
static void listIntPrint(Data data);
static void listIntDelete(Data data);

List* createIntList() {
	return createList(listIntEqual, listIntCompare, listIntPrint, listIntDelete);
}

int listIntEqual(Data data1, Data data2) {
	int* value1 = (int*)data1;
	int* value2 = (int*)data2;
	return (*value1 == *value2);
}
int listIntCompare(Data data1, Data data2) {
	int* value1 = (int*)data1;
	int* value2 = (int*)data2;
	return (*value1 < *value2);
}
void listIntPrint(Data data) {
	int* value = (int*)data;
	printf("%d", *value);
}
void listIntDelete(Data data) {
	free(data);
}
