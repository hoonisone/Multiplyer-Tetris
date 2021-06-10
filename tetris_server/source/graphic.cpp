#include <stdio.h>
#include <Windows.h>
#include "..\header\graphic.h"

static char _letter[4] = "*";


//DWORD WINAPI aaa(void* data) {
//	while (1) {
//	}
//	return 0;
//}
//static char ** board
//
//void graphicInit(int width, int height) {
//
//}

void graphicChangeColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void graphicMoveCursor(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void graphicMovePoint(int x, int y) {
	graphicMoveCursor(x * 2, y);
}

void graphicDrawPoint(int x, int y) {
	graphicMovePoint(x, y);
	printf("%s", _letter);
}

void graphicDrawVertical(int x, int y, int len) {
	for (int i = 0; i < len; i++) {
		graphicDrawPoint(x, y + i);
	}
}
void graphicDrawHorizontal(int x, int y, int len) {
	for (int i = 0; i < len; i++) {
		graphicDrawPoint(x + i, y);
	}
}
void graphicDrawRectangle(int x, int y, int width, int height) {
	graphicDrawVertical(x, y, height);
	graphicDrawVertical(x + width - 1, y, height);
	graphicDrawHorizontal(x, y, width);
	graphicDrawHorizontal(x, y + height - 1, width);
}

void graphicChangeLetter(char *letter) {
	strcpy(_letter, letter);
}

void graphicDrawLineRectangle(int x, int y, int width, int height) {
	graphicChangeLetter((char*)"¦­");
	graphicDrawVertical(x, y, height);
	graphicDrawVertical(x + width - 1, y, height);
	graphicChangeLetter((char*)"¦¬");
	graphicDrawHorizontal(x, y, width);
	graphicDrawHorizontal(x, y + height - 1, width);
	graphicChangeLetter((char*)"¦®");
	graphicDrawPoint(x, y);
	graphicChangeLetter((char*)"¦¯");
	graphicDrawPoint(x+width-1, y);
	graphicChangeLetter((char*)"¦°");
	graphicDrawPoint(x+width-1, y+height-1);
	graphicChangeLetter((char*)"¦±");
	graphicDrawPoint(x, y+height-1);
}