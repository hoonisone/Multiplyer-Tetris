#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
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
#include <windows.h>

void responseHandler(char* request, char* response) {
	strcpy(response, request);
	return;
}

char arr[100];
DWORD WINAPI aaa(void * data) {
	while(1){
		graphicMoveCursor(0, 0);
		system("cls");
		printf("***%s\n", arr);
	}
	return 0;
}

int main(int argc, char* argv[]) {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	//Test();
	//serverRun(5000, responseHandler);

	Screen* screen = screenCreateScreen();
	
	curBlockMoveLeft(screen);

	User* user = userCreateUser((char*)"hoonisone");
	userDrawUserInfor(user, 0, 0);

	drawFullScreen(screen, 0, 7);
	drawFullScreen(screen, 20, 7);
	drawFullScreen(screen, 40, 7);
	drawFullScreen(screen, 60, 7);
	char output[30][30];
	//for (int y = 0; y < 30; y++) {
	//	for (int x = 0; x < 30; x++) {
	//		output[y][x] = 0;
	//	}
	//}
	//memcpy(&output[10][5], "helÇÑlo", 10);
	//printf(&output[10][5]);

	int a = 0;
	HANDLE hThread = CreateThread(NULL, 0, aaa, NULL, 0, NULL);

	while (1){
		sprintf(arr, "%d", a++);
		//_sleep(100);
	}
	
}



