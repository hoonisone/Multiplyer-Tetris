#pragma once
#include <windows.h>
#include <stdlib.h>
#include "coordinate.h"

static Coordinate* create(void (*move)(int x, int y));
static void cursorMove(int x, int y);
static void pointMove(int x, int y);

static Coordinate* create(void (*move)(int x, int y)) {
	Coordinate* object = (Coordinate*)malloc(sizeof(Coordinate));
	object->move = move;
	return object;
}
Coordinate* createCursor() {
	static Coordinate* object = NULL;
	if (object == NULL) {
		object = create(cursorMove);
	}
	return object;
};
Coordinate* createPoint() {
	static Coordinate* object = NULL;
	if (object == NULL) {
		object = create(pointMove);
	}
	return object;
};

static void cursorMove(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
static void pointMove(int x, int y) {
	COORD pos = { 2*x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}