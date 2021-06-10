#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stringList.h"

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