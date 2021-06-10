#include "doubleList.h"
#include <stdio.h>
#include <stdlib.h>
#include "doubleList.h"

static int listDoubleEqual(Data data1, Data data2);
static int listDoubleCompare(Data data1, Data data2);
static void listDoublePrint(Data data);
static void listDoubleDelete(Data data);

List* createDoubleList() {
	return createList(listDoubleEqual, listDoubleCompare, listDoublePrint, listDoubleDelete);
}

int listDoubleEqual(Data data1, Data data2) {
	double* value1 = (double*)data1;
	double* value2 = (double*)data2;
	return (*value1 == *value2);
}
int listDoubleCompare(Data data1, Data data2) {
	double* value1 = (double*)data1;
	double* value2 = (double*)data2;
	return (*value1 < *value2);
}
void listDoublePrint(Data data) {
	double* value = (double*)data;
	printf("%fl", *value);
}
void listDoubleDelete(Data data) {
	free(data);
}