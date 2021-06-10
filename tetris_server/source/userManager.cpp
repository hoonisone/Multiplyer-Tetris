#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringList.h"
#include "user.h"
#include "file.h"
#include "string+.h"
#include "userManager.h"
#include "utill.h"
#include "test.h"
#include "error.h"



UserManager* umCreateUserManager(char* fileName) {
	UserManager* um = (UserManager*)malloc(sizeof(UserManager));
	strcpy_s(um->fileName, fileName);
	um->users = createList(userEqual, userCompare, userPrint, userDelete);
	return um;
}

void umReadUserInfor(UserManager* um) {
	List* lines = readFileIntoList(um->fileName);
	lines->emptyOut(um->users);
	for (int i = 0; i < lines->getSize(lines); i++) {
		char* line = (char*)lines->getElement(lines, i);
		List* tokens = split(line, (char*)"/");
		char* name   = (char*)lines->getElement(tokens, 0);
		int win      = atoi((char*)lines->getElement(tokens, 1));
		int draw     = atoi((char*)lines->getElement(tokens, 2));
		int lose     =  atoi((char*)lines->getElement(tokens, 3));
		User* user   = userCreateUser(name);
		user->win    = win;
		user->draw   = draw;
		user->lose   = lose;
		lines->pushBackElement(um->users, user);
	}
}
void umWriteUserInfor(UserManager* um) {
	List* lines = createStringList();
	List* users = um->users;
	for (int i = 0; i < lines->getSize(users); i++) {
		User* user = (User*)lines->getElement(users, i);
		char line[FILE_LINE_SIZE] = "";
		sprintf(line, "%s/%d/%d/%d", user->name, user->win, user->draw, user->lose);
		lines->pushBackElement(lines, newString(line));
	}
	writeListIntoFile(lines, um->fileName);
}
int  umUserExistenceCheck(UserManager* um, User* user) {
	return (um->users->findFirstElement(um->users, user) != -1);
}
void umEnrollUser(UserManager* um, User* user) {
	int count = um->users->findFirstElement(um->users, user);
	if (count != 0) {
		return;
	}

	um->users->pushBackElement(um->users, user);
}
void umRemoveUser(UserManager* um, User* user) {
	int idx = um->users->findFirstElement(um->users, user);
	if (idx == -1) {
		return;
	}

	um->users->popElement(um->users, idx);
}
void umModifyUser(UserManager* um, User* user) {
	if (um == NULL) {
		errorPrint("um is Null");
	}
	else if (user == NULL) {
		errorPrint("user is Null");
	}
	else if (umUserExistenceCheck(um, user)) {
		return;
	}
	int idx = um->users->findFirstElement(um->users, user);
	um->users->pushElement(um->users, idx, user);
	um->users->popElement(um->users, idx);
	umWriteUserInfor(um);
}


int  userEqual(const Data data1, const Data data2) {
	User* user1 = (User*)data1;
	User* user2 = (User*)data2;
	return strcmp(user1->name, user2->name) == 0;
}
int  userCompare(const Data data1, const Data data2) {
	User* user1 = (User*)data1;
	User* user2 = (User*)data2;
	return strcmp(user1->name, user2->name) == -1;
}
void userPrint(const Data data) {
	User* user = (User*)data;
	printf("\nName: %s\n", user->name);
	printf("win: %d | draw: %d | lose: %d\n", user->win, user->draw, user->lose);
}
void userDelete(Data data) {
	User* user = (User*)data;
	free(user);
}