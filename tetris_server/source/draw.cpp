#include <stdlib.h>
#include "draw.h"
#include <stdio.h>
static void horizontal(Draw* draw, int x, int y, int width);
static void vertical(Draw* draw, int x, int y, int height);
static void rect(Draw* draw, int x, int y, int width, int height);
static void rect2(Draw* draw, int x, int y, int width, int height);

Draw* createDraw(Coordinate* coordinate, Pen* pen) {
	Draw* object = (Draw*)malloc(sizeof(Draw));
	object->coordinate = coordinate;
	object->pen = pen;
	object->horizontal = horizontal;
	object->vertical = vertical;
	object->rect = rect;
	object->filledRect = rect2;
	return object;
}

static void horizontal(Draw* draw, int x, int y, int width) {
	Coordinate* coordinate = draw->coordinate;
	Pen* pen = draw->pen;
	for (int i = 0; i < width; i++) {
		coordinate->move(coordinate, x+i, y);
		pen->press(pen);
	}
}

static void vertical(Draw* draw, int x, int y, int height) {
	Coordinate* coordinate = draw->coordinate;
	Pen* pen = draw->pen;
	for (int i = 0; i < height; i++) {
		coordinate->move(coordinate, x, y + i);
		pen->press(pen);
	}
}

static void rect(Draw* draw, int x, int y, int width, int height) {
	horizontal(draw, x, y, width);
	vertical(draw, x, y, height);
	horizontal(draw, x , y + height - 1, width);
	vertical(draw, x + width - 1, y, height);
	return;
}

static void rect2(Draw* draw, int x, int y, int width, int height) {
	for (int i = 0; i < width; i++) {
		vertical(draw, x + i, y, height);
	}

	return;
}