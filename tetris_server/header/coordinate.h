#pragma once

#define CURSOR createCursor()
#define POINT createPoint()

typedef struct Coordinate {
	void (*move)(int x, int y);
}Coordinate;

Coordinate* createCursor();
Coordinate* createPoint();
