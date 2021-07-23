#pragma once

#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "graphic.h"

#define NAME_LENGTH 100


typedef struct Button {
	int x;
	int y;
	int width;
	int height;
	int selectFlag;
	char name[NAME_LENGTH];
	void(*action)();
} Button;

Button* buttonCreate(int x, int y, int width, int height, char *name, void(*action)()) {
	Button* object = (Button*)malloc(sizeof(Button));
	buttonX(object, x);
	buttonY(object, y);
	buttonSetWidth(object, width);
	buttonSetHeight(object, height);
	buttonSetName(object, name);
	object->action = action;

	return object;
}

void buttonX(Button* button, int x) {
	if (x <= 0)
		errorPrint("Range error");
	button->x = x;
}

void buttonY(Button* button, int y) {
	if (y <= 0)
		errorPrint("Range error");
	button->y = y;
}

void buttonSetWidth(Button* button, int width) {
	if(width <= 0)
		errorPrint("Range error");
	button->width = width;
}

void buttonSetHeight(Button* button, int height) {
	if (height <= 0)
		errorPrint("Range error");
	button->width = height;
}

void buttonSelect(Button* button) {
	button->selectFlag = 1;
}

void buttonUnselect(Button* button) {
	button->selectFlag = 0;
}

void buttonSetName(Button* button, char* name) {
	if (strlen(name) > 100) {
		errorPrint("The length of name is over buffer");
	}
	strcpy(button->name, name);
}

void draw(Button *button) {
	if (button->selectFlag = 0) {
		GRAPHIC->changeColor(BLACK);
	}
	else if (button->selectFlag = 1) {
		GRAPHIC->changeColor(GREEN);
	}
	GRAPHIC->drawLineRectangle(button->x, button->y, button->width, button->height);
	GRAPHIC->printText(button->x + 5, button->y + 5, button->name);
}