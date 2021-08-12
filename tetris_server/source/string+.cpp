#pragma warning(disable:4996)
#include <string.h>
#include "string+.h"
#include "stringList.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

char* createString(char* string) {
	char* token = (char*)malloc(sizeof(char) * (strlen(string) + 1));
	strcpy(token, string);
	return token;
}
List* split(char* string, char* key) {
	List* list = createStringList();
	char* copy = createString(string);
	char* ptr = strtok(copy, key);
	while (ptr != NULL) {
		list->pushBackElement(list, createString(ptr));
		ptr = strtok(NULL, key);
	}
	free(copy);
	return list;
}
vector<string> split(string s, string key) {
	int pos1 = 0, pos2;
	vector<string> tokens;
	while ((pos2 = s.find(key, pos1)) != -1) {
		tokens.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + key.size();
	}
	pos2 = s.size();
	tokens.push_back(s.substr(pos1, pos2 - pos1));
	return tokens;
}
