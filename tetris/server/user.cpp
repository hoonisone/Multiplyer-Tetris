#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "basic.h"

User* userCreateUser(char* name) {
	User* newUser = (User*)malloc(sizeof(User));
	strcpy(newUser->name, name);
	newUser->win = newUser->draw = newUser->lose = 0;
	newUser->login = False;
	return newUser;
}
void userLogin(User* user) {
	user->login = True;
}
void userLogout(User* user) {
	user->login = False;
}
void userWin(User* user) {
	user->win++;
}
void userDraw(User* user) {
	user->draw++;
}
void userLose(User* user) {
	user->lose++;
}
void userDeleteUser(User* user) {
	free(user);
}
void userPrintState(User* user) {
	printf("user state******************\n");
	printf("name  = %s", user->name);
	printf("win   = %d\n", user->win);
	printf("draw  = %d\n", user->draw);
	printf("lose  = %d\n", user->lose);
	printf("login = %d\n", user->login);
}