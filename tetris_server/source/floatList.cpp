#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int listFloatEqual(Data data1, Data data2) {
	float* value1 = (float*)data1;
	float* value2 = (float*)data2;
	return (*value1 == *value2);
}
int listFloatCompare(Data data1, Data data2) {
	float* value1 = (float*)data1;
	float* value2 = (float*)data2;
	return (*value1 < *value2);
}
void listFloatPrint(Data data) {
	float* value = (float*)data;
	printf("%f", *value);
}
void listFloatDelete(Data data) {
	free(data);
}