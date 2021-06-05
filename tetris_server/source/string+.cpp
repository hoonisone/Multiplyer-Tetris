#pragma warning(disable:4996)
#include <string.h>
#include "string+.h"
#include "list.h"

List* split(char* string, char* key) {
	List* list = listCreateList(listStringEqual, listStringCompare, listStringPrint, listStringDelete);
	char* ptr = strtok(string, key);
	while (ptr != NULL) {
		listPushBackElement(list, ptr);
		ptr = strtok(NULL, key);
	}
	return list;
}
