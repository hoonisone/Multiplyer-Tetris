#pragma once
#include <windows.h>

#define CURSOR createCursor()
#define POINT createPoint()
#define COORDINATE createCoordinate

typedef struct Coordinate {
	int x, y;
	void (*move)(Coordinate* coordinate, int x, int y);
}Coordinate;

Coordinate* createCoordinate(int x, int y);

Coordinate* createCursor();
Coordinate* createPoint();

COORD getXY();