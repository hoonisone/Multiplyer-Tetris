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
	int floorCheck;

	// shadowBlock
	Block* shadowBlock;
	int shadowBlockY;

	// nextBlock
	Block* nextBlock;

	// holdBlock
	Block* holdBlock;

	// Data
	int** blockBoard;
}Screen;

Screen* screenCreateScreen();
void screenChangeSize(Screen* screen, int width, int height);
Block* screenNewBlock();
void screenSetNextBlock(Screen* screen);
void screenSetCurBlock(Screen* screen);

void curBlockMoveTo(Screen* screen, int x, int y);

void curBlockMoveUp(Screen* screen);

void curBlockMoveDown(Screen* screen);

void curBlockMoveRight(Screen* screen);

void curBlockMoveLeft(Screen* screen);



int curBlockPositionPermitCheck(Screen* screen);
int curBlockCrashCheck(Screen* screen);
void screenInitShadowBlock(Screen* screen);
void screenUpdateShadowBlock(Screen* screen);
void screenUpdateShadowBlockPosition(Screen* screen);
void pressCurBlock(Screen* screen);
void screenHoldBlock(Screen* screen);
int curBlockOutOfRangeCheck(Screen* screen);
int isInRange(Screen* screen, int x, int y);

void screenDrawFullScreen(Screen* screen, int X, int Y);
void drawBoardFrame(Screen* screen, int X, int Y);
void drawBlockFrame(Screen* screen, int X, int Y);
void drawBoard(Screen* screen, int X, int Y);
void drawCurBlock(Screen* screen, int X, int Y);

void drawShadowBlock(Screen* screen, int X, int Y);

void drawNextBlock(Screen* screen, int X, int Y);

void drawHoldBlock(Screen* screen, int X, int Y);
