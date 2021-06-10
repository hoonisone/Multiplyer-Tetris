#include "intList.h"
#include <stdio.h>
#include <stdlib.h>

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
