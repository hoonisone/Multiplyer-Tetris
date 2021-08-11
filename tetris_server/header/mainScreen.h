//#pragma once
//#include "graphic.h"
//#include "block.h"
//#include "subScreen.h"
//#include "mainBlock.h"
//
//#define SCREEN_DEFAULT_WIDTH  10
//#define SCREEN_DEFAULT_HEIGHT 20
//
//#define SCREEN_DEFAULT_LETTER "бс"
//#define SCREEN_DEFAULT_COLOR WHITE
//#define MAIN_SCREEN mainScreenFunctionCreate()
//
//typedef struct MainScreen {
//	// position, size
//	int x, y, width, height, color;
//	char letter[4];
//
//	BlockBoard* blockBoard;
//	MainBlock* mainBlock;
//}MainScreen;
//
//typedef struct MainScreenFunction {
//	MainScreen* (*create)(int x, int y, int width, int height);
//	void (*moveTo)(MainScreen* mainScreen, int x, int y);
//	void (*setLetter)(MainScreen* mainScreen, char* letter);
//	void (*setColor)(MainScreen* mainScreen, Color color);
//	void (*moveDown)(MainScreen* mainScreen);
//	void (*moveRight)(MainScreen* mainScreen);
//	void (*moveLeft)(MainScreen* mainScreen);
//	void (*turnRight)(MainScreen* mainScreen);
//	void (*turnLeft)(MainScreen* mainScreen);
//	Block* (*changeMainBlock)(MainScreen* mainScreen, Block* block);
//	void (*pressMainBlock)(MainScreen* mainScreen, Block* newBlock);
//	void (*pullDown)(MainScreen* mainScreen, Block* newBlock);
//}MainScreenFunction;
//
//MainScreenFunction* mainScreenFunctionCreate();