#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "tetrisScreen.h"
#include "tetrisBlock.h"

static int colors[BLOCK_COLOR_NUM] = { LIGHT_BLUE, LIGHT_GREEN, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, BRIGHT_WHITE, LIGHT_AQUA };

Screen* screenCreateScreen()
{
	Screen* newScreen = (Screen*)malloc(sizeof(Screen));
	newScreen->x = 0;
	newScreen->y = 0;
	newScreen->width = DEFAULT_WIDTH;
	newScreen->height = DEFAULT_HEIGHT;
	newScreen->curBlock = NULL;
	newScreen->nextBlock = NULL;
	screenSetNextBlock(newScreen);
	screenSetNewBlock(newScreen);
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
}

Block* screenNewBlock() {
	srand(time(NULL));
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

void screenSetNewBlock(Screen* screen) {
	if (screen->curBlock != NULL) {
		free(screen->curBlock);
	}
	screen->curBlock = screen->nextBlock;
	screen->nextBlock = NULL;
	screen->curBlockX = screen->width/2 - BLOCK_WIDTH/2;
	screen->curBlockY = 0;
	screenSetNextBlock(screen);
}

//void blockMoveTo(Block* block, int x, int y)
//{
//	block->x = x;
//	block->y = y;
//}
//void blockMoveUp(Block* block)
//{
//	block->y--;
//}
//void blockMoveDown(Block* block)
//{
//	block->y++;
//}
//void blockMoveRight(Block* block)
//{
//	block->x++;
//}
//void blockMoveLeft(Block* block)
//{
//	block->x--;
//}

