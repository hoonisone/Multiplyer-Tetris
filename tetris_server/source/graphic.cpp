#include <stdio.h>
#include <Windows.h>
#include "graphic.h"
#include <windows.h>
#include "stringList.h"
#include <string.h>
#include "string+.h"

static void graphicInit();
static void graphicSetFullScreen();
static void graphicSetScreenSize(int width, int height);
static void graphicSetColor(Color color);
static void graphicMoveCursor(int x, int y);
static void graphicMovePoint(int x, int y);
static void graphicDrawPoint(int x, int y);
static void graphicDrawVertical(int x, int y, int len);
static void graphicDrawHorizontal(int x, int y, int len);
static void graphicDrawRectangle(int x, int y, int width, int height);
static void graphicSetLetter(char* letter);
static void graphicDrawLineRectangle(int x, int y, int width, int height);
void graphicDelete(GraphicManager* gm);
void graphicManagerPrintText(int x, int y, char* text);
static void graphicDrawFilledRectangle(int x, int y, int width, int height);
static void graphicSetBackgroundColor(int color);
static char letter[LETTER_SIZE];

GraphicManager* createGraphicManager()
{
	static GraphicManager* object = NULL;
	if (object == NULL) {
		object = (GraphicManager*)malloc(sizeof(GraphicManager));
		object->init = graphicInit;
		object->setFullScreen = graphicSetFullScreen;
		object->setScreenSize = graphicSetScreenSize;
		object->setColor = graphicSetColor;
		object->moveCursor = graphicMoveCursor;
		object->movePoint = graphicMovePoint;
		object->drawPoint = graphicDrawPoint;
		object->drawVertical = graphicDrawVertical;
		object->drawHorizontal = graphicDrawHorizontal;
		object->drawRectangle = graphicDrawRectangle;
		object->drawFilledRectangle = graphicDrawFilledRectangle;
		object->setLetter = graphicSetLetter;
		object->drawLineRectangle = graphicDrawLineRectangle;
		object->setBackgroundColor = graphicSetBackgroundColor;
		object->del = graphicDelete;
		object->printText = graphicManagerPrintText;
	}
	return object;
}

void graphicInit() {
	graphicSetLetter(DEFAULT_LETTER_LETTER);
	graphicSetColor(DEFAULT_LETTER_COLOR);
	graphicSetBackgroundColor(DEFAULT_BACKGROUND_COLOR);
}

void graphicSetFullScreen() {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

void graphicSetScreenSize(int width, int height) {
	char order[100];
	sprintf(order, "mode con cols=%d lines=%d", width, height, 100);
	system(order);
}

void graphicSetColor(Color color) {
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
	for (int i = 0; i < height; i++) {
		graphicDrawHorizontal(x, y+i, width);
	}
}

void graphicSetLetter(char *_letter) {
	strcpy(letter, _letter);
}

void graphicDrawLineRectangle(int x, int y, int width, int height) {

	graphicSetLetter((char*)"¦­");
	
	graphicDrawVertical(x, y, height);
	

	graphicDrawVertical(x + width - 1, y, height);
	graphicSetLetter((char*)"¤Ñ");
	graphicDrawHorizontal(x, y, width-1);
	graphicDrawHorizontal(x, y + height - 1, width-1);
	graphicSetLetter((char*)"¦®");
	graphicDrawPoint(x, y);
	graphicSetLetter((char*)"¦¯");
	graphicDrawPoint(x+width-1, y);
	graphicSetLetter((char*)"¦°");
	graphicDrawPoint(x+width-1, y+height-1);
	graphicSetLetter((char*)"¦±");
	graphicDrawPoint(x, y+height-1);
	
}

void graphicSetBackgroundColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((color & 0xf) << 4) | (info.wAttributes & 0xf));
}

void graphicDrawRect(int x, int y, int w, int h) {
	for (int i = 0; i <= w; i++) {
		graphicDrawVertical(x+i, y, h);
	}
}

void graphicDelete(GraphicManager * gm) {
	free(gm);
}

void graphicManagerPrintText(int x, int y, char* text) {
	graphicMoveCursor(x, y);
	printf("%s", text);
}
//void graphicPrintPicture(int x, int y, const char** picture, int len) {
//	for (int i = 0; i < len; i++) {
//		GRAPHIC->moveCursor(x, y + i);
//		printf("%s", picture[i]);
//	}
//}
//const char* T[10] = { "¡á¡á¡á¡á¡á¡á¡á¡á",
//					"¡á¡á¡á¡á¡á¡á¡á¡á",
//					"      ¡á¡á      ",
//					"      ¡á¡á      ",
//					"      ¡á¡á      ",
//					"      ¡á¡á      ",
//					"      ¡á¡á      ",
//					"      ¡á¡á      ",
//					"      ¡á¡á      ",
//					"      ¡á¡á      " };
//graphicPrintPicture(5, 5, T, sizeof(T) / sizeof(const char*))

void graphicPrintT(int x, int y, Color color)
{
	graphicSetColor(color);
	graphicMoveCursor(x, y);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 1);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 2);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 3);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 4);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 5);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 6);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 7);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 8);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 9);
	printf("      ¡á¡á      ");
}



void graphicPrintE(int x, int y, Color color)
{
	graphicSetColor(color);
	graphicMoveCursor(x, y);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 1);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 2);
	printf("¡á¡á            ");
	graphicMoveCursor(x, y + 3);
	printf("¡á¡á            ");
	graphicMoveCursor(x, y + 4);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 5);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 6);
	printf("¡á¡á            ");
	graphicMoveCursor(x, y + 7);
	printf("¡á¡á            ");
	graphicMoveCursor(x, y + 8);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 9);
	printf("¡á¡á¡á¡á¡á¡á¡á¡á");
}

void graphicPrintR(int x, int y, Color color)
{
	graphicSetColor(color);
	graphicMoveCursor(x, y);
	printf("¡á¡á¡á¡á¡á¡á    ");
	graphicMoveCursor(x, y + 1);
	printf("¡á¡á¡á¡á¡á¡á¡á  ");
	graphicMoveCursor(x, y + 2);
	printf("¡á¡á      ¡á¡á¡á");
	graphicMoveCursor(x, y + 3);
	printf("¡á¡á      ¡á¡á¡á");
	graphicMoveCursor(x, y + 4);
	printf("¡á¡á¡á¡á¡á¡á¡á  ");
	graphicMoveCursor(x, y + 5);
	printf("¡á¡á¡á¡á¡á¡á    ");
	graphicMoveCursor(x, y + 6);
	printf("¡á¡á    ¡á¡á¡á   ");
	graphicMoveCursor(x, y + 7);
	printf("¡á¡á      ¡á¡á¡á");
	graphicMoveCursor(x, y + 8);
	printf("¡á¡á        ¡á¡á");
	graphicMoveCursor(x, y + 9);
	printf("¡á¡á        ¡á¡á");
}

void graphicPrintI(int x, int y, Color color)
{
	graphicSetColor(color);
	graphicMoveCursor(x, y);
	printf("  ¡á¡á¡á¡á¡á¡á  ");
	graphicMoveCursor(x, y + 1);
	printf("  ¡á¡á¡á¡á¡á¡á  ");
	graphicMoveCursor(x, y + 2);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 3);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 4);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 5);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 6);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 7);
	printf("      ¡á¡á      ");
	graphicMoveCursor(x, y + 8);
	printf("  ¡á¡á¡á¡á¡á¡á  ");
	graphicMoveCursor(x, y + 9);
	printf("  ¡á¡á¡á¡á¡á¡á  ");
}

void graphicPrintS(int x, int y, Color color)
{
	graphicSetColor(color);
	graphicMoveCursor(x, y);
	printf("    ¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 1);
	printf("  ¡á¡á¡á¡á¡á¡á¡á");
	graphicMoveCursor(x, y + 2);
	printf("¡á¡á¡á          ");
	graphicMoveCursor(x, y + 3);
	printf("¡á¡á¡á          ");
	graphicMoveCursor(x, y + 4);
	printf("  ¡á¡á¡á¡á¡á    ");
	graphicMoveCursor(x, y + 5);
	printf("    ¡á¡á¡á¡á¡á  ");
	graphicMoveCursor(x, y + 6);
	printf("          ¡á¡á¡á");
	graphicMoveCursor(x, y + 7);
	printf("          ¡á¡á¡á");
	graphicMoveCursor(x, y + 8);
	printf("¡á¡á¡á¡á¡á¡á¡á  ");
	graphicMoveCursor(x, y + 9);
	printf("¡á¡á¡á¡á¡á¡á    ");
}
