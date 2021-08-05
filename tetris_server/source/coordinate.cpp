#pragma once
#include <windows.h>
#include <stdlib.h>
#include "coordinate.h"

static Coordinate* createCoordinate(void (*move)(int x, int y));
static void move(Coordinate* coordinate, int x, int y);

Coordinate* createCoordinate(int x, int y) {
	Coordinate* object = (Coordinate*)malloc(sizeof(Coordinate));
	object->move = move;
	object->x = x;
	object->y = y;
	return object;
}
Coordinate* createCursor() {
	static Coordinate* object = NULL;
	if (object == NULL) {
		object = createCoordinate(1, 1);
	}
	return object;
};
Coordinate* createPoint() {
	static Coordinate* object = NULL;
	if (object == NULL) {
		object = createCoordinate(2, 1);
	}
	return object;
};

static void move(Coordinate* coordinate, int x, int y) {
	COORD pos = { coordinate->x*x, coordinate->y*y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD getXY() {
	COORD Cur;
	CONSOLE_SCREEN_BUFFER_INFO a;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
	Cur.X = a.dwCursorPosition.X;
	Cur.Y = a.dwCursorPosition.Y;
	return Cur;
}