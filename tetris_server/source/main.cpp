#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <conio.h>
#include <time.h>
#include "server.h"
#include "error.h"
#include "stringList.h"
#include "user.h"
#include "utill.h"
#include "string+.h"
#include "file.h"
#include "userManager.h"
#include "tetrisScreen.h"
#include "scoreManager.h"
#include "math+.h"
#include <windows.h>
#include "timer.h"

void responseHandler(char* request, char* response) {
	strcpy(response, request);
	return;
}

List* printList;

DWORD WINAPI printAll(void * data) {
	while(1){
		while (!printList->isEmpty(printList)) {
			system("cls");
			char* text = (char*)printList->getElement(printList, 0);
			printf("num: %d\ncur: %s", printList->getSize(printList), text);
			printList->popElement(printList, 0);
			free(text);
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	Timer* t1 = createTimer();
	Timer* t2 = createTimer();

	while (1) {
		/*printf("time1 = %d\n", t1->getTime(t1));
		printf("time2 = %d\n", t2->getTime(t2));
		t2->init(t2);*/
		printf("time = %d\n", clock());
	}
	//Test();
	//serverRun(5000, responseHandler);

	//Screen* screen = screenCreateScreen();
	//
	//curBlockMoveLeft(screen);

	//User* user = userCreateUser((char*)"hoonisone");
	//userDrawUserInfor(user, 0, 0);

	//drawFullScreen(screen, 0, 7);
	//drawFullScreen(screen, 20, 7);
	//drawFullScreen(screen, 40, 7);
	//drawFullScreen(screen, 60, 7);
	//char output[30][30];
	////for (int y = 0; y < 30; y++) {
	////	for (int x = 0; x < 30; x++) {
	////		output[y][x] = 0;
	////	}
	////}
	////memcpy(&output[10][5], "helÇÑlo", 10);
	////printf(&output[10][5]);

	//int a = 0;
	//printList = createStringList();
	//HANDLE hThread = CreateThread(NULL, 0, printAll, NULL, 0, NULL);
	//char buffer[100];
	//while (1){
	//	sprintf(buffer, "%d", clock());
	//	printList->pushBackElement(printList, newString(buffer));
	//	//_sleep(1000);
	//}
	
}



