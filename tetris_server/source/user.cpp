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
	static char buffer[100];

	graphicManager->drawLineRectangle(X +  0, Y + 0, 17, 3);
	graphicManager->drawLineRectangle(X +  0, Y + 2, 6, 3);
	graphicManager->drawLineRectangle(X +  5, Y + 2, 5, 3);
	graphicManager->drawLineRectangle(X + 10, Y + 2, 5, 3);
	graphicManager->drawLineRectangle(X + 15, Y + 2, 5, 3);

	graphicManager->drawLineRectangle(X +  0, Y + 4, 5, 3);
	graphicManager->drawLineRectangle(X +  5, Y + 4, 5, 3);
	graphicManager->drawLineRectangle(X + 10, Y + 4, 5, 3);
	graphicManager->drawLineRectangle(X + 15, Y + 4, 5, 3);
	

	graphicManager->changeLetter((char*)"¦²");
	graphicManager->drawPoint(X + 0, Y + 2);
	graphicManager->drawPoint(X + 0, Y + 4);

	graphicManager->changeLetter((char*)"¦´");
	graphicManager->drawPoint(X + 20, Y + 2);
	graphicManager->drawPoint(X + 20, Y + 4);

	graphicManager->changeLetter((char*)"¦³");
	graphicManager->drawPoint(X + 5, Y + 2);
	graphicManager->drawPoint(X + 10, Y + 2);
	graphicManager->drawPoint(X + 15, Y + 2);

	graphicManager->changeLetter((char*)"¦¶");
	graphicManager->drawPoint(X + 5, Y + 4);
	graphicManager->drawPoint(X + 10, Y + 4);
	graphicManager->drawPoint(X + 15, Y + 4);

	graphicManager->changeLetter((char*)"¦µ");
	graphicManager->drawPoint(X + 5, Y + 6);
	graphicManager->drawPoint(X + 10, Y + 6);
	graphicManager->drawPoint(X + 15, Y + 6);

	//sprintf(buffer, "%10s", user->name);
	//graphicManager->printText(X + 1, Y + 1, buffer);

	//sprintf(buffer, " %4s", "WIN");
	//graphicManager->printText(X + 1, Y + 3, buffer);

	//sprintf(buffer, " %4s", "DRAW");
	//graphicManager->printText(X + 5, Y + 3, buffer);

	//sprintf(buffer, " %4s", "LOSE");
	//graphicManager->printText(X + 9, Y + 3, buffer);

	//sprintf(buffer, " %5d", user->win);
	//graphicManager->printText(X + 1, Y + 5, buffer);

	//sprintf(buffer, " %5d", user->draw);
	//graphicManager->printText(X + 5, Y + 5, buffer);

	//sprintf(buffer, " %5d", user->lose);
	//graphicManager->printText(X + 9, Y+5, buffer);
}