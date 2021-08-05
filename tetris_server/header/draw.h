#pragma once
#include "coordinate.h"
#include "pen.h"

#define DRAW createDraw

typedef struct Draw{
	Coordinate* coordinate;
	Pen* pen;
	void (*horizontal)(Draw* draw, int x, int y, int width);
	void (*vertical)(Draw* draw, int x, int y, int height);
	void (*rect)(Draw* draw, int x, int y, int width, int height);
	void (*filledRect)(Draw* draw, int x, int y, int width, int height);
}Draw;

Draw* createDraw(Coordinate* coordinate, Pen* pen);