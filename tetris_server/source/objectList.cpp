#include "doubleList.h"
#include <stdio.h>
#include <stdlib.h>

static int listObjectEqual(Data data1, Data data2);
static int listObjectCompare(Data data1, Data data2);
static void listObjectPrint(Data data);
static void listObjectDelete(Data data);

List* createObjectList() {
	return createList(listObjectEqual, listObjectCompare, listObjectPrint, listObjectDelete);
}

int listObjectEqual(Data data1, Data data2) {

	return (data1 == data2);
}
int listObjectCompare(Data data1, Data data2) {
	return (data1 < data2);
}
void listObjectPrint(Data data) {
	printf("%p", data);
}
void listObjectDelete(Data data) {
	free(data);
}