#pragma once
#include "graphic.h"
#include "block.h"
#include "subScreen.h"
#include "mainBlock.h"

#define SCREEN_DEFAULT_WIDTH  10
#define SCREEN_DEFAULT_HEIGHT 20

#define SCREEN_DEFAULT_LETTER "бс"
#define SCREEN_DEFAULT_COLOR WHITE
#define SCREEN getScreenFunction()

typedef struct MainScreen {
	// position, size
	int x, y, width, height, color;
	char letter[4];

	BlockBoard* blockBoard;
	MainBlock* mainBlock;
	SubScreen* subScreen;

}MainScreen;

//typedef struct MainScreenFunction {
//
//}ScreenFunction;

MainScreen* mainScreenCreate(int x, int y, int boardWidth, int boardHeight);
//void screenMoveTo(MainScreen* screen, int x, int y);
//MainScreenFunction* getScreenFunction();


