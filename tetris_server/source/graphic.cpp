#include <stdio.h>
#include <Windows.h>
#include "graphic.h"
#include <windows.h>
#include "stringList.h"
#include <string.h>

#define LETTER_SIZE 4

static GraphicManager* createGraphicManager();
static void graphicSetFullScreen();
static void graphicSetScreenSize(int width, int height);
static void graphicChangeColor(int color);
static void graphicMoveCursor(int x, int y);
static void graphicMovePoint(int x, int y);
static void graphicDrawPoint(int x, int y);
static void graphicDrawVertical(int x, int y, int len);
static void graphicDrawHorizontal(int x, int y, int len);
static void graphicDrawRectangle(int x, int y, int width, int height);
static void graphicChangeLetter(char* letter);
static void graphicDrawLineRectangle(int x, int y, int width, int height);
void graphicDelete(GraphicManager* gm);
static void graphicManagerFillInternalMethod(GraphicManager* gm);
void graphicManagerPrintText(int x, int y, char* text);
static void graphicDrawFilledRectangle(int x, int y, int width, int height);

static char letter[LETTER_SIZE];

GraphicManager* _graphicManager = NULL;


GraphicManager* getGraphicManager()
{
	if (_graphicManager == NULL) {
		_graphicManager = createGraphicManager();
	}
	return _graphicManager;
}

GraphicManager* createGraphicManager()
{
	GraphicManager* object = (GraphicManager*)malloc(sizeof(GraphicManager));
	graphicManagerFillInternalMethod(object);
	return object;
}

static void graphicManagerFillInternalMethod(GraphicManager* gm) {
	gm->setFullScreen = graphicSetFullScreen;
	gm->setScreenSize = graphicSetScreenSize;
	gm->changeColor = graphicChangeColor;
	gm->moveCursor = graphicMoveCursor;
	gm->movePoint = graphicMovePoint;
	gm->drawPoint = graphicDrawPoint;
	gm->drawVertical = graphicDrawVertical;
	gm->drawHorizontal = graphicDrawHorizontal;
	gm->drawRectangle = graphicDrawRectangle;
	gm->drawFilledRectangle = graphicDrawFilledRectangle;
	gm->changeLetter = graphicChangeLetter;
	gm->drawLineRectangle = graphicDrawLineRectangle;
	gm->del = graphicDelete;
	gm->printText = graphicManagerPrintText;
}

void graphicSetFullScreen() {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

void graphicSetScreenSize(int width, int height) {
	char order[100];
	sprintf(order, "mode con cols=%d lines=%d", width, height, 100);
	system(order);
}

void graphicChangeColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void graphicMoveCursor(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void graphicMovePoint(int x, int y) {
	graphicMoveCursor(x * 2, y);
}

void graphicDrawPoint(int x, int y) {
	graphicMovePoint(x, y);
	printf("%s", letter);
}

void graphicDrawVertical(int x, int y, int len) {
	for (int i = 0; i < len; i++) {
		graphicDrawPoint(x, y + i);
		
	}
}
void graphicDrawHorizontal(int x, int y, int len) {
	for (int i = 0; i < len; i++) {
		graphicDrawPoint(x + i, y);
	}
}
void graphicDrawRectangle(int x, int y, int width, int height) {
		graphicDrawVertical(x, y, height);
		graphicDrawVertical(x + width - 1, y, height);
		graphicDrawHorizontal(x, y, width);
		graphicDrawHorizontal(x, y + height - 1, width);
}
void graphicDrawFilledRectangle(int x, int y, int width, int height) {
	for (int i = y; i < y + height; i++) {
		graphicDrawHorizontal(x, y, width);
	}
}




void graphicChangeLetter(char *_letter) {
	strcpy(letter, _letter);
}

void graphicDrawLineRectangle(int x, int y, int width, int height) {

	graphicChangeLetter((char*)"¦­");
	
	graphicDrawVertical(x, y, height);
	

	graphicDrawVertical(x + width - 1, y, height);
	graphicChangeLetter((char*)"¤Ñ");
	graphicDrawHorizontal(x, y, width);
	graphicDrawHorizontal(x, y + height - 1, width);
	graphicChangeLetter((char*)"¦®");
	graphicDrawPoint(x, y);
	graphicChangeLetter((char*)"¦¯");
	graphicDrawPoint(x+width-1, y);
	graphicChangeLetter((char*)"¦°");
	graphicDrawPoint(x+width-1, y+height-1);
	graphicChangeLetter((char*)"¦±");
	graphicDrawPoint(x, y+height-1);
	
}

void graphicDelete(GraphicManager * gm) {
	free(gm);
}

void graphicManagerPrintText(int x, int y, char* text) {
	graphicMovePoint(x, y);
	printf("%s", text);
}