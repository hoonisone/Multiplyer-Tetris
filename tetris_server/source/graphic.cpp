#include <stdio.h>
#include <Windows.h>
#include "..\header\graphic.h"

static char _letter[4] = "*";

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

void drawPoint(int x, int y) {
	graphicMovePoint(x, y);
	printf("%s", _letter);
}

void drawVertical(int x, int y, int len) {
	for (int i = 0; i < len; i++) {
		drawPoint(x, y + i);
	}
}
void drawHorizontal(int x, int y, int len) {
	for (int i = 0; i < len; i++) {
		drawPoint(x + i, y);
	}
}
void drawRectangle(int x, int y, int width, int height) {
	drawVertical(x, y, height);
	drawVertical(x + width - 1, y, height);
	drawHorizontal(x, y, width);
	drawHorizontal(x, y + height - 1, width);
}

void graphicChangeLetter(char *letter) {
	strcpy(_letter, letter);
}

void drawLineRectangle(int x, int y, int width, int height) {
	graphicChangeLetter((char*)"¦­");
	drawVertical(x, y, height);
	drawVertical(x + width - 1, y, height);
	graphicChangeLetter((char*)"¦¬");
	drawHorizontal(x, y, width);
	drawHorizontal(x, y + height - 1, width);
	graphicChangeLetter((char*)"¦®");
	drawPoint(x, y);
	graphicChangeLetter((char*)"¦¯");
	drawPoint(x+width-1, y);
	graphicChangeLetter((char*)"¦°");
	drawPoint(x+width-1, y+height-1);
	graphicChangeLetter((char*)"¦±");
	drawPoint(x, y+height-1);
}