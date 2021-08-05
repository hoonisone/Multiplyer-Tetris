#include <stdio.h>
#include <windows.h>
#include "pen.h"
#include <string.h>
#include "coordinate.h"

static Shape textShape;
static Pen* usingPen = NULL;

static void press(Pen* pen);
static void setTextShape(Shape _textShape);
static void setTextColor(Color textColor);
static void setBackgroundColor(Color backgroundColor);

Pen* createPen(Color textColor, Color backgroundColor, Shape textShape, int width, int height) {
	Pen* object = (Pen*)malloc(sizeof(Pen));
	object->textColor = textColor;
	object->backgroundColor = backgroundColor;
	memcpy(object->textShape, textShape, sizeof(object->textShape));
	object->settingFlag = 0;
	object->press = press;
	object->width = width;
	object->height = height;
	return object;
};

static void setTextShape(Shape _textShape) {
	memcpy(textShape, _textShape, sizeof(textShape));
}

static void setTextColor(Color textColor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
}

static void setBackgroundColor(Color backgroundColor) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((backgroundColor & 0xf) << 4) | (info.wAttributes & 0xf));
}

static void press(Pen* pen) {
	if (pen->settingFlag == 0) {
		setTextColor(pen->textColor);
		setBackgroundColor(pen->backgroundColor);
		setTextShape(pen->textShape);
		pen->settingFlag = 1;
		if (usingPen != NULL) {
			usingPen->settingFlag = 0;
			usingPen = pen;
		}
	}
	COORD coord = getXY();
	int X = coord.X;
	int Y = coord.Y;
	for (int y = 0; y < pen->height; y++) {
		CURSOR->move(CURSOR, X, Y + y);
		printf("%s", pen->textShape[y]);
	}
}