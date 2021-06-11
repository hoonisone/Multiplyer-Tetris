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
GraphicManager* gm;

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
	graphicManager->setFullScreen();
	graphicManager->changeLetter((char*)"aa");
	graphicManager->drawPoint(10, 10);

	//int a;
	//((char*)(&a))[0];
	//char arr[9];
	//strcpy(arr, "¦¡ ¦¡");
	//arr[5] = 8;
	//arr[6] = 'a';
	//arr[7] = 8;
	//arr[8] = NULL;
	//printf("%s", arr);
	//printf("a");
	////¦¡bb b
	//while (1);

	//Test();
	//serverRun(5000, responseHandler);

	Screen* screen = screenCreateScreen();

	//User* user = userCreateUser((char*)"hoonisone");
	//userDrawUserInfor(user, 10, 0);
	
	while (1) {
		screenDrawFullScreen(screen, 10, 10);

	}
	while (1);
}



