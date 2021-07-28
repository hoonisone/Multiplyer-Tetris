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
#include "mainScreen.h"
#include "scoreManager.h"
#include "math+.h"
#include <windows.h>
#include "timer.h"
#include "tetris.h"
#include "graphic.h"
#include "block.h"
#include "tetris.h"
#include "button.h"

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
	//Test();
	//serverRun(5000, responseHandler);
	
	//MainScreen* mainScreen = MAIN_SCREEN->create(0, 0, 12, 22);
	//
	//MAIN_SCREEN->moveRight(mainScreen);
	//MAIN_SCREEN->moveRight(mainScreen);
	//MAIN_SCREEN->moveRight(mainScreen);
	//MAIN_SCREEN->moveRight(mainScreen);
	//MAIN_SCREEN->moveRight(mainScreen);
	//MAIN_SCREEN->moveDown(mainScreen);
	//MAIN_SCREEN->moveDown(mainScreen);
	//MAIN_SCREEN->moveDown(mainScreen);
	//MAIN_SCREEN->moveDown(mainScreen);
	//MAIN_SCREEN->moveDown(mainScreen);
	//MAIN_SCREEN->moveDown(mainScreen);
	//MAIN_SCREEN->pressMainBlock(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//MAIN_SCREEN->pullDown(mainScreen, BLOCK->createRandomBlock());
	//while (1);
	//Tetris* t1 = TETRIS->create();
	//TETRIS->mainHandler(t1);
	//int arr[10];
	//printf("%d\n", sizeof(arr)/sizeof(int));

	//arr[0] = 999;
	//printf("%d\n", arr[0]);
	//a(arr);
	//textPrintMiddle(3, 5, 10, 10, (char*)"hello\nhellohello\nhellohello");
	Button* but= buttonCreate(20, 10, 20, 5, (char*)"Hello", NULL, ALIGN_RIGHT, 1, (char*)"?", GREEN, YELLOW);
	draw(but);
}
