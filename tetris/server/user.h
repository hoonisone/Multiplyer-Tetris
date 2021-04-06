#pragma once
#include "list.h"
#include "basic.h"
#define NAME_SIZE 100

typedef struct User {
	char name[NAME_SIZE];
	int win, draw, lose;
	Bool login;
}User;

User* userCreateUser(char* name);
void userLogin(User* user);
void userLogout(User* user);
void userWin(User* user);
void userDraw(User* user);
void userLose(User* user);
void userDeleteUser(User* user);
void userPrintState(User* user);