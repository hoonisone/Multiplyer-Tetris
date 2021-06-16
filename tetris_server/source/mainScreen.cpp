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

MainScreen* mainScreenCreate(int x, int y, int width, int height);
void mainScreenMoveTo(MainScreen* mainScreen, int x, int y);
void mainScreenSetLetter(MainScreen* mainScreen, char* letter);
void mainScreenSetColor(MainScreen* mainScreen, Color color);
void mainScreenMoveDown(MainScreen* mainScreen);
void mainScreenMoveRight(MainScreen* mainScreen);
void mainScreenMoveLeft(MainScreen* mainScreen);
void mainScreenTurnRight(MainScreen* mainScreen);
void mainScreenTurnLeft(MainScreen* mainScreen);
void mainScreenPullDown(MainScreen* mainScreen, Block* newBlock);
Block* mainScreenChangeMainBlock(MainScreen* mainScreen, Block* block);
void mainScreenPressMainBlock(MainScreen* mainScreen, Block* newBlock);
static void mainScreenEraseFrame(MainScreen* mainScreen);
static void mainScreenDrawFrame(MainScreen* mainScreen);

MainScreenFunction* mainScreenFunctionCreate() {
	static MainScreenFunction* object = NULL;
	if (object == NULL) {
		object = (MainScreenFunction*)malloc(sizeof(MainScreenFunction));
		object->create = mainScreenCreate;
		object->moveTo = mainScreenMoveTo;
		object->setLetter = mainScreenSetLetter;
		object->setColor = mainScreenSetColor;
		object->moveDown = mainScreenMoveDown;
		object->moveRight = mainScreenMoveRight;
		object->moveLeft = mainScreenMoveLeft;
		object->turnRight = mainScreenTurnRight;
		object->turnLeft = mainScreenTurnLeft;
		object->changeMainBlock = mainScreenChangeMainBlock;
		object->pressMainBlock = mainScreenPressMainBlock;
		object->pullDown = mainScreenPullDown;
	}
	return object;
}
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
	strcpy(object->letter, (char*)MAIN_SCREEN_DEFAULT_LETTER);
	object->blockBoard = BLOCK_BOARD->create(x + 1, y + 1, width-2, height-2);	// 프레임 두께 1
	
	object->mainBlock = MAIN_BLOCK->create(object->blockBoard, BLOCK->createRandomBlock());
	
	mainScreenDrawFrame(object);
	return object;
}
void mainScreenMoveTo(MainScreen* mainScreen, int x, int y) {
	if (mainScreen == NULL) {
		errorPrint("mainScreen is NULL");
	}
	mainScreenEraseFrame(mainScreen);
	mainScreen->x = x;
	mainScreen->y = y;
	BLOCK_BOARD->moveTo(mainScreen->blockBoard, x+1, y+1);
	MAIN_BLOCK->changeBlock(mainScreen->mainBlock, mainScreen->mainBlock->bodyBlock);	// 동일한 블록으로 체인지 -> 자리 초기화 됨
	mainScreenDrawFrame(mainScreen);
}
void mainScreenSetLetter(MainScreen* mainScreen, char* letter) {
	if (mainScreen == NULL) {
		errorPrint("mainScreen is NULL");
	}
	if (letter == NULL) {
		errorPrint("letter is NULL");
	}
	strcpy(mainScreen->letter, letter);
	mainScreenDrawFrame(mainScreen);
}
void mainScreenSetColor(MainScreen* mainScreen, Color color) {
	mainScreen->color = color;
	mainScreenDrawFrame(mainScreen);
}
void mainScreenMoveDown(MainScreen* mainScreen) {
	MAIN_BLOCK->moveDown(mainScreen->mainBlock);
}
void mainScreenMoveRight(MainScreen* mainScreen) {
	MAIN_BLOCK->moveRight(mainScreen->mainBlock);
}
void mainScreenMoveLeft(MainScreen* mainScreen) {
	MAIN_BLOCK->moveLeft(mainScreen->mainBlock);
}
void mainScreenTurnRight(MainScreen* mainScreen) {
	MAIN_BLOCK->turnRight(mainScreen->mainBlock);
}
void mainScreenTurnLeft(MainScreen* mainScreen) {
	MAIN_BLOCK->turnLeft(mainScreen->mainBlock);
}
void mainScreenPullDown(MainScreen* mainScreen, Block* newBlock) {
	MAIN_BLOCK->pullDown(mainScreen->mainBlock);
	mainScreenPressMainBlock(mainScreen, newBlock);
}

Block* mainScreenChangeMainBlock(MainScreen* mainScreen, Block* block) {
	return MAIN_BLOCK->changeBlock(mainScreen->mainBlock, block);
}
void mainScreenPressMainBlock(MainScreen* mainScreen, Block * newBlock) {
	BlockBoard* blockBoard = mainScreen->blockBoard;
	MainBlock* mainBlock = mainScreen->mainBlock;
	BLOCK_BOARD->pressBlock(blockBoard, mainBlock->bodyBlock);
	Block* oldBlock = MAIN_BLOCK->changeBlock(mainBlock, newBlock);
	BLOCK_BOARD->pressBlock(blockBoard, oldBlock);
	free(oldBlock);
}
static void mainScreenEraseFrame(MainScreen* mainScreen) {
	if (mainScreen == NULL) {
		errorPrint("mainScreen is NULL");
	}
	GRAPHIC->changeLetter(EMPTY_LETTER);
	GRAPHIC->changeColor(EMPTY_COLOR);
	GRAPHIC->drawRectangle(mainScreen->x, mainScreen->y, mainScreen->width, mainScreen->height);
}
static void mainScreenDrawFrame(MainScreen* mainScreen) {
	if (mainScreen == NULL) {
		errorPrint("mainScreen is NULL");
	}
	GRAPHIC->changeLetter(mainScreen->letter);
	GRAPHIC->changeColor(mainScreen->color);
	GRAPHIC->drawRectangle(mainScreen->x, mainScreen->y, mainScreen->width, mainScreen->height);
}