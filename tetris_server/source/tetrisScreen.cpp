#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tetrisScreen.h"
#include "tetrisBlock.h"
#include "math+.h"
#include "graphic.h"

static int colors[BLOCK_COLOR_NUM] = { LIGHT_BLUE, LIGHT_GREEN, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, BRIGHT_WHITE, LIGHT_AQUA };

Screen* screenCreateScreen()
{
	Screen* newScreen = (Screen*)malloc(sizeof(Screen));
	newScreen->x = 0;
	newScreen->y = 0;
	newScreen->width = 0;
	newScreen->height = 0;
	strcpy(newScreen->letter, SCREEN_DEFAULT_LETTER);
	newScreen->color = SCREEN_DEFAULT_COLOR;
	newScreen->blockBoard = NULL;
	screenChangeSize(newScreen, SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT);
	newScreen->curBlock = NULL;
	newScreen->nextBlock = NULL;
	screenSetNextBlock(newScreen);
	screenSetCurBlock(newScreen);
	return newScreen;
}

void screenChangeSize(Screen* screen, int width, int height) {
	int** tmp = (int**)malloc(sizeof(int*) * height);
	for (int i = 0; i < height; i++) {
		tmp[i] = (int*)calloc(width, sizeof(int));
	}
	int minWidth = (width < screen->width) ? width : screen->width;
	int minHeight = (height < screen->height) ? height : screen->height;
	for (int i = 0; i < minHeight; i++) {
		memcpy(tmp[height - 1 - i], screen->blockBoard[screen->height - 1 - i], minWidth);
	}
	for (int i = 0; i < screen->height; i++) {
		free(screen->blockBoard[i]);
	}
	free(screen->blockBoard);

	screen->blockBoard = tmp;
	screen->width = width;
	screen->height = height;
}

Block* screenNewBlock() {
	//srand(time(NULL));
	int color = rand() % BLOCK_COLOR_NUM;
	int shape = rand() % BLOCK_SHAPE_NUM;
	return blockCreateBlock(colors[color], shape);
}

void screenSetNextBlock(Screen* screen) {
	if (screen->nextBlock != NULL) {
		free(screen->nextBlock);
	}
	screen->nextBlock = screenNewBlock();
}

void screenSetCurBlock(Screen* screen) {
	if (screen->curBlock != NULL) {
		free(screen->curBlock);
	}
	screen->curBlock = screen->nextBlock;
	screen->nextBlock = NULL;
	screen->curBlockX = screen->width/2 - BLOCK_WIDTH/2;
	screen->curBlockY = 0;
	screenSetNextBlock(screen);
}

void curBlockMoveTo(Screen* screen, int x, int y)
{
	int preX = screen->curBlockX;
	int preY = screen->curBlockY;

	screen->curBlockX = x;
	screen->curBlockY = y;

	if (!curBlockPositionPermitCheck(screen)) {
		screen->curBlockX = preX;
		screen->curBlockY = preY;
	}
}

void curBlockMoveUp(Screen* screen)
{
	screen->curBlockY--;
	if (!curBlockPositionPermitCheck(screen))
		screen->curBlockY++;
}

void curBlockMoveDown(Screen* screen)
{
	screen->curBlockY++;
	if (!curBlockPositionPermitCheck(screen))
		screen->curBlockY--;
}

void curBlockMoveRight(Screen* screen)
{
	screen->curBlockX++;
	if (!curBlockPositionPermitCheck(screen))
		screen->curBlockX--;
}

void curBlockMoveLeft(Screen* screen)
{
	screen->curBlockX--;
	if (!curBlockPositionPermitCheck(screen))
		screen->curBlockX++;
}

int curBlockPositionPermitCheck(Screen* screen) {
	if (curBlockCrashCheck(screen))
		return 0;
	if (curBlockOutOfRangeCheck(screen))
		return 0;
	return 1;
}

int curBlockCrashCheck(Screen* screen) {
	screen->curBlockX;
	screen->curBlockY;
	screen->width;
	screen->height;
	screen->blockBoard;

	int screenX1 = 0;
	int screenY1 = 0;
	int screenX2 = screen->width-1;
	int screenY2 = screen->height-1;

	int blockX1 = screen->curBlockX;
	int blockY1 = screen->curBlockY;
	int blockX2 = blockX1 + BLOCK_WIDTH-1;
	int blockY2 = blockY1 + BLOCK_HEIGHT-1;

	int commonX1 = greater(screenX1, blockX1);
	int commonY1 = greater(screenY1, blockY1);
	int commonX2 = smaller(screenX2, blockX2);
	int commonY2 = smaller(screenY2, blockY2);

	for (int y = commonY1; y <= commonY2; y++) {
		for (int x = commonX1; x <= commonX2; x++) {
			if (screen->blockBoard[y][x] != 0 && blockGetShape(screen->curBlock)[y-commonY1][x-commonX1] != 0) {
				return 1;
			}
		}
	}
	return 0;
}

int isInRange(Screen* screen, int x, int y) {
	if (0 <= x && x < screen->width)
	if (0 <= y && y < screen->height)
		return 1;
	return 0;
}

int curBlockOutOfRangeCheck(Screen* screen) {
	int blockX1 = screen->curBlockX;
	int blockY1 = screen->curBlockY;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (blockGetShape(screen->curBlock)[y][x] == 0)
				continue;
			if (!isInRange(screen, x + blockX1, y + blockY1))
				return 1;
		}
	}
	return 0;
}

void pressCurBlock(Screen * screen) {
	int color = screen->curBlock->color;
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (blockGetShape(screen->curBlock)[y][x] == 1) {
				int relativeX = x + screen->curBlockX;
				int relativeY = y + screen->curBlockY;
				screen->blockBoard[relativeY][relativeX] = color;
			}
		}
	}
}

void drawScreen(Screen * screen, int X, int Y) {
	drawBoardFrame(screen, X, Y);
	drawBoard(screen, X+1, Y+1);
	drawCurBlock(screen, X+1, Y+1);
	drawNextBlock(screen, X+screen->width+1, Y);
	drawHoldBlock(screen, X + screen->width + 1, Y+BLOCK_HEIGHT+2);
}

void drawBoardFrame(Screen * screen, int X, int Y) {
	graphicChangeLetter(screen->letter);
	graphicChangeColor(screen->color);
	drawRectangle(X, Y, screen->width+2, screen->height+2);
}

void drawBoard(Screen* screen, int X, int Y) {
	for (int y = 0; y < screen->height; y++) {
		for (int x = 0; x < screen->width; x++) {
			int color = screen->blockBoard[y][x];
			if (color != 0) {
				graphicChangeLetter(screen->letter);
				graphicChangeColor(color);
				drawPoint(X + x, Y + y);
			}
		}
	}
}

void drawCurBlock(Screen* screen, int X, int Y) {
	blockDrawBlock(screen->curBlock, X + screen->curBlockX, Y + screen->curBlockY);
}

void drawNextBlock(Screen* screen, int X, int Y) {
	graphicChangeLetter(screen->letter);
	graphicChangeColor(screen->color);
	drawRectangle(X, Y, BLOCK_WIDTH+2, BLOCK_HEIGHT+2+1);
	graphicChangeColor(WHITE);
	graphicMovePoint(X + 1, Y + 1);

	printf("  NEXT  ")
	blockDrawBlock(screen->nextBlock, X+1, Y+2);
}

void drawHoldBlock(Screen* screen, int X, int Y) {
	graphicChangeLetter(screen->letter);
	graphicChangeColor(screen->color);
	drawRectangle(X, Y, BLOCK_WIDTH + 2, BLOCK_HEIGHT + 2 + 1);
	graphicChangeColor(WHITE);
	graphicMovePoint(X + 1, Y + 1);
	printf("  HOLD  ");
	blockDrawBlock(screen->nextBlock, X + 1, Y + 2);////////////////////////////// need to modify
}