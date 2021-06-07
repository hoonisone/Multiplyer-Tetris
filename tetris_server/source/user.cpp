#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "graphic.h"

User* userCreateUser(char* name) {
	User* newUser = (User*)malloc(sizeof(User));
	strcpy(newUser->name, name);
	newUser->win = newUser->draw = newUser->lose = 0;
	newUser->login = 0;
	return newUser;
}
void userLogin(User* user) {
	user->login = 1;
}
void userLogout(User* user) {
	user->login = 0;
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

void userDrawUserInfor(User* user, int X, int Y) {
	drawLineRectangle(0, 0, 17, 3);
	drawLineRectangle(0, 2, 5, 3);
	drawLineRectangle(4, 2, 5, 3);
	drawLineRectangle(8, 2, 5, 3);
	drawLineRectangle(12, 2, 5, 3);
	drawLineRectangle(0, 4, 5, 3);
	drawLineRectangle(4, 4, 5, 3);
	drawLineRectangle(8, 4, 5, 3);
	drawLineRectangle(12, 4, 5, 3);

	graphicChangeLetter((char*)"¦²");
	drawPoint(0, 2);
	drawPoint(0, 4);

	graphicChangeLetter((char*)"¦´");
	drawPoint(16, 2);
	drawPoint(16, 4);

	graphicChangeLetter((char*)"¦³");
	drawPoint(4, 2);
	drawPoint(8, 2);
	drawPoint(12, 2);

	graphicChangeLetter((char*)"¦¶");
	drawPoint(4, 4);
	drawPoint(8, 4);
	drawPoint(12, 4);

	graphicChangeLetter((char*)"¦µ");
	drawPoint(4, 6);
	drawPoint(8, 6);
	drawPoint(12, 6);

	graphicMovePoint(1, 1);
	printf("%10s", user->name);

	graphicMovePoint(1, 3);
	printf(" %4s", "WIN");
	graphicMovePoint(5, 3);
	printf(" %4s", "DRAW");
	graphicMovePoint(9, 3);
	printf(" %4s", "LOSE");

	graphicMovePoint(1, 5);
	printf(" %5d", user->win);
	graphicMovePoint(5, 5);
	printf(" %5d", user->draw);
	graphicMovePoint(9, 5);
	printf(" %5d", user->lose);
	

	//graphicMoveCursor(1, 3);
	//printf("  WIN: %7d\n", 100);
	//graphicMoveCursor(1, 4);
	//printf(" DRAW: %7d\n", 100);
	//graphicMoveCursor(1, 5);
	//printf(" LOSE: %7d\n", 100);
}