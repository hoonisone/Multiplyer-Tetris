#pragma once
#include "graphic.h"
#include "tetrisBlock.h"
#define DEFAULT_WIDTH  10
#define DEFAULT_HEIGHT 20
#define BLOCK_COLOR_NUM 7


typedef struct Screen {
	// position, size
	int x, y, width, height;
	
	// curBlock
	Block* curBlock;
	int curBlockX;
	int curBlockY;

	// NextBlock
	Block* nextBlock;

	// Data
	int** blockBoard;
}Screen;

Screen* screenCreateScreen();
void screenChangeSize(Screen* screen, int width, int height);
Block* screenNewBlock();
void screenSetNextBlock(Screen* screen);
void screenSetNewBlock(Screen* screen);