#pragma once
#include "graphic.h"
#include "tetrisBlock.h"
#define SCREEN_DEFAULT_WIDTH  10
#define SCREEN_DEFAULT_HEIGHT 20
#define BLOCK_COLOR_NUM 7
#define SCREEN_DEFAULT_LETTER "бс"
#define SCREEN_DEFAULT_COLOR WHITE

typedef struct Screen {
	// position, size
	int x, y, width, height;
	int color;
	char letter[4];
	
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
void screenSetCurBlock(Screen* screen);

int curBlockPositionPermitCheck(Screen* screen);
int curBlockCrashCheck(Screen* screen);
void pressCurBlock(Screen* screen);
int curBlockOutOfRangeCheck(Screen* screen);
int isInRange(Screen* screen, int x, int y);

void drawScreen(Screen* screen, int X, int Y);
void drawBoardFrame(Screen* screen, int X, int Y);
void drawBoard(Screen* screen, int X, int Y);
void drawCurBlock(Screen* screen, int X, int Y);