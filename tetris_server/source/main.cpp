#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <conio.h>

#include "server.h"
#include "error.h"
#include "list.h"
#include "user.h"
#include "utill.h"
#include "string+.h"
#include "file.h"
#include "userManager.h"
#include "tetrisScreen.h"
#include "scoreManager.h"
#include "math+.h"



void responseHandler(char* request, char* response) {
	strcpy(response, request);
	return;
}

void Test() {
	ListTestAll();
	ScoreManagerTest();
	MathPlusTest();
}

int main(int argc, char* argv[]) {
	//Test();
	//serverRun(5000, responseHandler);




	Screen* screen = screenCreateScreen();
	
	curBlockMoveLeft(screen);

	User* user = userCreateUser((char*)"hoonisone");
	userDrawUserInfor(user, 0, 0);

	drawScreen(screen, 0, 7);

	while (1);


}

