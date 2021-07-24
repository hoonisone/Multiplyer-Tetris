#pragma once

#define NAME_LENGTH 100

typedef struct Button {
	int x;
	int y;
	int width;
	int height;
	int selectFlag;
	char name[NAME_LENGTH];
	int textAlign;
	void(*action)();
} Button;

Button* buttonCreate(int x, int y, int width, int height, char* name, int textAlign, void(*action)());
void buttonSetX(Button* button, int x);
void buttonSetY(Button* button, int y);
void buttonSetWidth(Button* button, int width);
void buttonSetHeight(Button* button, int height);
void buttonSelect(Button* button);
void buttonUnselect(Button* button);
void buttonSetName(Button* button, char* name);
void buttonSetTextAlgin(Button* button, int textAlgin);
void draw(Button* button);
