#pragma warning(disable:4996)
#define _HAS_STD_BYTE 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <conio.h>
#include <time.h>
#include <vector>
#include <string>
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
#include "Button.h"
#include "ColorPainter.h"
#include "ColorPrinter.h"
#include "system.h"
#include "ButtonManager.h"
#include "string+.h"
#include <format>
#include <iostream>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

using namespace std;
void action(Button* button);

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
	//Button* but= buttonCreate(20, 10, 7, 3, (char*)"Hello", NULL, ALIGN_MIDDLE, 1, (char*)"*", LIGHT_BLUE, WHITE, BLACK);
	//draw(but);
	
	//Draw* draw = DRAW(POINT, PEN(YELLOW, BLACK, (char*)"."));
	//draw->filledRect(draw, 5, 5, 12, 22);
	//char image[10][10] = { "¡à" };
	//Pen* pen = PEN(BLUE, BLACK, image, 3, 1);
	//Draw * draw = DRAW(COORDINATE(3, 1), pen);
	//draw->rect(draw, 3, 3, 10, 22);
	//Button(5, 5, 100, 10, "hello", BLUE, BLACK, true, RED, BLACK, CENTER, BOTTOM).draw();
	ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
	ColorPainter painter({ "¡à" }, WHITE, BLACK);
	ColorPrinter selectPrinter(CENTER, MIDDLE, RED, BLACK);
	ColorPainter selectPainter({ "¡à" }, RED, BLACK);
	ButtonManager bm = ButtonManager(5, 5);
	int x = 30;
	int y = 0;
	int w = 15;
	int h = 5;
	bm.enroll(new Button(x, y+5, w, h, "start", painter.newObject(), printer.newObject(), selectPainter.newObject(), selectPrinter.newObject(), true), 3, 0);
	bm.enroll(new Button(x, y + 9, w, h, "»ç¶ûÇØ¿ä ±èº­¸®", &painter, &printer, &selectPainter, &selectPrinter, true), 3, 1);
	bm.enroll(new Button(x, y + 13, w, h, "mh", &painter, &printer, &selectPainter, &selectPrinter, true), 3, 2);
	bm.enroll(new Button(x, y + 17, w, h, "hello", &painter, &printer, &selectPainter, &selectPrinter, true), 3, 3);
	bm.enroll(new Button(x, y + 21, w, h, "exit", &painter, &printer, &selectPainter, &selectPrinter, true), 3, 4);
	bm.draw();
	bm.setAction(action);
	char c;
	while (1) {
		if (_kbhit()) {
			c = _getch();
			if (c == -32) {
				c = _getch();
				switch (c) {
				case LEFT:
					
					break;
				case RIGHT:

					break;
				case UP:
					bm.up();
					bm.draw();
					break;
				case DOWN:
					bm.down();
					bm.draw();
					break;
				}
			}
			else if (c == ' ') {
				bm.click();
			}
			else if (c == 'q') {
				printf("Á¾·á");
				return 0;
			}
		}
	}

}

void action(Button* button) {
	Consol::move(0, 0);
	cout << button->text;
}
