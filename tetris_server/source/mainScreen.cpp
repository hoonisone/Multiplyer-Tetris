#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mainScreen.h"
#include "block.h"
#include "math+.h"
#include "graphic.h"
#include "error.h"
#include "random.h"
#include "subScreen.h"
#include "blockBoard.h"
#include "mainBlock.h"

#define MAIN_SCREEN_DEFAULT_COLOR WHITE
#define MAIN_SCREEN_DEFAULT_LETTER "■"

static Block* mainScreenCreateRandomBlock();
static void mainScreenSetLetter(MainScreen* mainScreen, char* letter);
static void mainScreenMoveTo(MainScreen* mainScreen, int x, int y);
static void mainScreenEraseFrame(MainScreen* mainScreen);
static void mainScreenDrawFrame(MainScreen* mainScreen);

MainScreen* mainScreenCreate(int x, int y, int width, int height) {
	MainScreen* object = (MainScreen*)malloc(sizeof(MainBlock));
	if (object == NULL) {
		errorPrint("memory allocation failed");
	}
	object->x = x;
	object->y = y;
	object->width = width;
	object->height = height;
	object->color = MAIN_SCREEN_DEFAULT_COLOR;
	mainScreenSetLetter(object, (char*)MAIN_SCREEN_DEFAULT_LETTER);
	mainScreenDrawFrame(object);
	object->blockBoard = BLOCK_BOARD->create(x + 1, y + 1, width-2, height-2);	// 프레임 두께 1
	object->mainBlock = MAIN_BLOCK->create(object->blockBoard, mainScreenCreateRandomBlock());
	object->subScreen = SUB_SCREEN->create(x + width - 1, y, BLOCK_WIDTH + 2, height);
	return object;
}
static Block* mainScreenCreateRandomBlock() {
	int shape = RANDOM->getValue() % BLOCK_SHAPE_NUM;
	int angle = RANDOM->getValue() % BLOCK_ANGLE_NUM;
	Color color = RANDOM->getValue() % BLOCK_COLOR_NUM;
	return BLOCK->create(0, 0,shape, angle, color);
}

static void mainScreenSetLetter(MainScreen* mainScreen, char* letter) {
	strcpy(mainScreen->letter, letter);
}
static void mainScreenMoveTo(MainScreen* mainScreen, int x, int y) {
	mainScreenEraseFrame(mainScreen);
	mainScreen->x = x;
	mainScreen->y = y;
	mainScreenDrawFrame(mainScreen);
	BLOCK_BOARD->moveTo(mainScreen->blockBoard, x+1, y+1);
	MAIN_BLOCK->changeMainBlock(mainScreen->mainBlock, mainScreen->mainBlock->mainBlock);	// 동일한 블록으로 체인지 -> 자리 초기화 됨
	SUB_SCREEN->moveTo(mainScreen->subScreen, mainScreen->width - 1, y);
}
static void mainScreenEraseFrame(MainScreen* mainScreen) {
	GRAPHIC->changeLetter(EMPTY_LETTER);
	GRAPHIC->changeColor(EMPTY_COLOR);
	GRAPHIC->drawRectangle(mainScreen->x, mainScreen->y, mainScreen->width, mainScreen->height);
}
static void mainScreenDrawFrame(MainScreen* mainScreen) {
	GRAPHIC->changeLetter(mainScreen->letter);
	GRAPHIC->changeColor(mainScreen->color);
	GRAPHIC->drawRectangle(mainScreen->x, mainScreen->y, mainScreen->width, mainScreen->height);
}