#include <stdio.h>
#include <windows.h>
#include "pen.h"
#include <string.h>

static Shape textShape;
static Pen* usingPen = NULL;

static void press(Pen* pen);
static void setTextShape(Shape _textShape);
static void setTextColor(Color textColor);
static void setBackgroundColor(Color backgroundColor);

Pen* createPen(Color textColor, Color backgroundColor, Shape textShape) {
	Pen* object = (Pen*)malloc(sizeof(Pen));
	object->textColor = textColor;
	object->backgroundColor = backgroundColor;
	strcpy(object->textShape, textShape);
	object->settingFlag = 0;
	object->press = press;
	return object;
};

static void setTextShape(Shape _textShape) {
	strcpy(textShape, _textShape);
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
	printf("%s", textShape);
}