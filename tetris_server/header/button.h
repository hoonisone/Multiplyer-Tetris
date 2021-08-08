#pragma once
#include "graphic.h"

#define NAME_LENGTH 100

typedef struct Button {
	int x, y, width, height;
	char name[NAME_LENGTH];
	void(*action)();
	int textAlign;
	int borderFlag;
	char borderChar[4];
	int borderColor, nameColor, backgroundColor;
} Button;

Button* buttonCreate(int x, int y, int width, int height, char* name, void(*action)(), int textAlign = ALIGN_MIDDLE,
					 int borderFlag = 1, char* borderChar = (char*)"*", int borderColor = WHITE, 
					 int nameColor = WHITE, int bgColor = BLACK);
void buttonSetX(Button* button, int x);
void buttonSetY(Button* button, int y);
void buttonSetWidth(Button* button, int width);
void buttonSetHeight(Button* button, int height);
void buttonSetName(Button* button, char* name);
void buttonSetTextAlgin(Button* button, int textAlgin);
void buttonSetAction(Button* button, void(*action)());
void buttonSetBorderFlag(Button* button, int flag);
void buttonSetBorderChar(Button* button, char *ch);
void buttonSetBorderColor(Button* button, int color);
void buttonSetNameColor(Button* button, int color);
void buttonSetBgColor(Button* button, int color);
void draw(Button* button);
