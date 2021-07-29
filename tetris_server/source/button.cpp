#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "graphic.h"
#include "string+.h"
#include "button.h"
#include <stdio.h>
#include <windows.h>

Button* buttonCreate(int x, int y, int width, int height, char* name, void(*action)(), int textAlign,
					 int borderFlag, char *borderChar, int borderColor, int nameColor, int bgColor) {
	Button* object = (Button*)malloc(sizeof(Button));
	buttonSetX(object, x);
	buttonSetY(object, y);
	buttonSetWidth(object, width);
	buttonSetHeight(object, height);
	buttonSetName(object, name);
	buttonSetTextAlgin(object, textAlign);
	buttonSetAction(object, action);
	buttonSetBorderFlag(object, borderFlag);
	buttonSetBorderChar(object, (char*)borderChar);
	buttonSetBorderColor(object, borderColor);
	buttonSetNameColor(object, nameColor);
	buttonSetBgColor(object, bgColor);
	return object;
}

void buttonSetX(Button* button, int x) {
	if (x <= 0)
		errorPrint("Range error");
	button->x = x;
}

void buttonSetY(Button* button, int y) {
	if (y <= 0)
		errorPrint("Range error");
	button->y = y;
}

void buttonSetWidth(Button* button, int width) {
	if (width <= 0)
		errorPrint("Range error");
	button->width = width;
}

void buttonSetHeight(Button* button, int height) {
	if (height <= 0)
		errorPrint("Range error");
	button->height = height;
}

void buttonSetName(Button* button, char* name) {
	if (strlen(name) > 100) {
		errorPrint("The length of name is over buffer");
	}
	strcpy(button->name, name);
}

void buttonSetTextAlgin(Button* button, int textAlgin) {
	if (textAlgin < 0 || textAlgin > 2)
		errorPrint("Range error");
	button->textAlign = textAlgin;
}

void buttonSetAction(Button* button, void(*action)()) {
	button->action = action;
}

void buttonSetBorderFlag(Button* button, int flag) {
	button->borderFlag = flag;
}

void buttonSetBorderChar(Button* button, char* ch) {
	strcpy(button->borderChar, ch);
}

void buttonSetBorderColor(Button* button, int color) {
	button->borderColor = color;
}

void buttonSetNameColor(Button* button, int color) {
	button->nameColor = color;
}

void buttonSetBgColor(Button* button, int color) {
	button->backgroundColor = color;
}

void draw(Button* button) {
	if (button->borderFlag == 1) {
		GRAPHIC->setLetter((char*)button->borderChar);
		GRAPHIC->setColor(button->borderColor);
		GRAPHIC->drawRectangle(button->x, button->y, button->width, button->height);
	}
	GRAPHIC->setColor(button->nameColor);
	GRAPHIC->setBackgroundColor(button->backgroundColor);
	GRAPHIC->setLetter((char*)"  ");
	GRAPHIC->drawFilledRectangle(button->x + 1, button->y + 1, button->width - 2, button->height - 2);
	textPrintAlign((button->x + 1) * 2, button->y + 1, button->width - 2, button->height - 2, button->name, button->textAlign);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 100, 100 });
	GRAPHIC->init();
}
