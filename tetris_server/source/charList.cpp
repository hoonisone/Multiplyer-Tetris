#include "charList.h"
#include <stdio.h>
#include <stdlib.h>

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