#include <stdio.h>
#include <Windows.h>

static char _letter = '*';

void graphicChangeColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void graphicMoveCursor(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawPoint(int x, int y) {
	graphicMoveCursor(x*2, y);
	printf("%c", _letter);
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

void graphicChangeLetter(char letter) {
	_letter = letter;
}