#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "user.h"
#include "file.h"
#include "string+.h"
#include "userManager.h"
#include "utill.h"
#include "test.h"

UserManager* umCreateUserManager(char* fileName) {
	UserManager* um = (UserManager*)malloc(sizeof(UserManager));
	strcpy_s(um->fileName, fileName);
	um->users = listCreateList(userEqual, userCompare, userPrint);
	return um;
}

void umReadUserInfor(UserManager* um) {
	List* lines = readFileIntoList(um->fileName);
	listEmptyOut(um->users);
	for (int i = 0; i < listGetSize(lines); i++) {
		char* line = (char*)listGetElement(lines, i);
		List* tokens = split(line, (char*)"/");
		char* name   = (char*)listGetElement(tokens, 0);
		int win      = atoi((char*)listGetElement(tokens, 1));
		int draw     = atoi((char*)listGetElement(tokens, 2));
		int lose     =  atoi((char*)listGetElement(tokens, 3));
		User* user   = userCreateUser(name);
		user->win    = win;
		user->draw   = draw;
		user->lose   = lose;
		listPushBackElement(um->users, user);
	}
}
void umWriteUserInfor(UserManager* um) {
	List* lines = listCreateList(listStringEqual, listStringCompare, listStringPrint);
	List* users = um->users;
	for (int i = 0; i < listGetSize(users); i++) {
		User* user = (User*)listGetElement(users, i);
		char line[FILE_LINE_SIZE] = "";
		sprintf(line, "%s/%d/%d/%d", user->name, user->win, user->draw, user->lose);
		listPushBackElement(lines, newString(line));
	}
	writeListIntoFile(lines, um->fileName);
}
void umEnrollUser(UserManager* um, User* user) {
	int count = listFindFirstElement(um->users, user);
	if (count != 0) {
		return;
	}

	listPushBackElement(um->users, user);
}

void umRemoveUser(UserManager* um, User* user) {
	int idx = listFindFirstElement(um->users, user);
	if (idx == -1) {
		return;
	}

	listPopElement(um->users, idx);
}

int userEqual(const Data data1, const Data data2) {
	User* user1 = (User*)data1;
	User* user2 = (User*)data2;
	return strcmp(user1->name, user2->name) == 0;
}
int userCompare(const Data data1, const Data data2) {
	User* user1 = (User*)data1;
	User* user2 = (User*)data2;
	return strcmp(user1->name, user2->name) == -1;
}
void userPrint(const Data data) {
	User* user = (User*)data;
	printf("\nName: %s\n", user->name);
	printf("win: %d | draw: %d | lose: %d\n", user->win, user->draw, user->lose);
}