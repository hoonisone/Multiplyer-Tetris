#pragma warning(disable:4996)
#include <string.h>
#include "string+.h"
#include "stringList.h"

List* split(char* string, char* key) {
	List* list = createStringList();
	char* ptr = strtok(string, key);
	while (ptr != NULL) {
		list->pushBackElement(list, ptr);
		ptr = strtok(NULL, key);
	}
	return list;
}