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
	newScreen->x = newScreen->y = 0;
	newScreen->width = newScreen->height = 0;
	strcpy(newScreen->letter, SCREEN_DEFAULT_LETTER);
	newScreen->color = SCREEN_DEFAULT_COLOR;
	newScreen->blockBoard = NULL;
	screenChangeSize(newScreen, SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT);
	newScreen->curBlock = NULL;
	newScreen->floorCheck = 0;
	newScreen->shadowBlock = blockCreateBlock(0, 0);	// shadowBlock은 계속 유지되면서 curBlock을 memcpy하여 사용
	
	newScreen->nextBlock = newScreen->holdBlock = NULL;
	
	screenSetNextBlock(newScreen);
	screenSetCurBlock(newScreen);
	screenInitShadowBlock(newScreen);
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
	screen->floorCheck = 0; // cur블록이 바닥에 닿았다는 사실을 초기화
	screenUpdateShadowBlock(screen);
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
	else
		screenUpdateShadowBlockPosition(screen);
}

void curBlockMoveDown(Screen* screen)
{
	screen->curBlockY++;
	if (!curBlockPositionPermitCheck(screen)){
		screen->floorCheck = 1;
		screen->curBlockY--;
	}
}

void curBlockMoveRight(Screen* screen)
{
	screen->curBlockX++;
	if (!curBlockPositionPermitCheck(screen))
		screen->curBlockX--;
	else
		screenUpdateShadowBlockPosition(screen);
}

void curBlockMoveLeft(Screen* screen)
{
	screen->curBlockX--;
	if (!curBlockPositionPermitCheck(screen))
		screen->curBlockX++;
	else
		screenUpdateShadowBlockPosition(screen);
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
void screenInitShadowBlock(Screen* screen){
	strcpy(screen->shadowBlock->letter, "□");
	screenUpdateShadowBlock(screen);
}

void screenUpdateShadowBlock(Screen* screen) {
	
	screen->shadowBlock->angle = screen->curBlock->angle;
	screen->shadowBlock->color = screen->curBlock->color;
	screen->shadowBlock->shape = screen->curBlock->shape;
	screenUpdateShadowBlockPosition(screen);
}

void screenUpdateShadowBlockPosition(Screen* screen) {
	int originY = screen->curBlockY;
	while (!screen->floorCheck) {	// curBlock을 바닥 까지 내린다.
		curBlockMoveDown(screen);
	}
	screen->floorCheck = 0;	// 임시로 내린 것이기 때문에 바닥에 닿았는지에 대한 check값 복구
	screen->shadowBlockY = screen->curBlockY;
	curBlockMoveTo(screen, screen->curBlockX, originY);
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

void screenHoldBlock(Screen* screen) {
	if (screen->holdBlock == NULL) {
		screen->holdBlock = screen->curBlock;
		screen->curBlock = NULL;
		screenSetCurBlock(screen);
	}
	else {
		// setCurBlock()를 이용하여 블록 위치를 초기화 하는데 이용
		Block* temp = screen->nextBlock;	// nextBlock임시 저장
		screen->nextBlock = screen->holdBlock; // next블록을 hold블록으로 대체하여 setCurBlock시 hold블록이 나오도록 함
		screen->holdBlock = screen->curBlock;
		screen->curBlock = NULL;
		screenSetCurBlock(screen);
		free(screen->nextBlock);	// 불 필요한 setCurBlock()에서 생긴 next블록 삭제
		screen->nextBlock = temp;	// nextBlock 복구
	}
}
void drawBoardFrame(Screen * screen, int X, int Y) {
	graphicChangeLetter(screen->letter);
	graphicChangeColor(screen->color);
	graphicDrawRectangle(X, Y, screen->width+2, screen->height+2);
}
void drawBlockFrame(Screen* screen, int X, int Y) {
	graphicChangeLetter(screen->letter);
	graphicChangeColor(screen->color);
	graphicDrawRectangle(X, Y, BLOCK_WIDTH+2, screen->height + 2);
}
void drawBoard(Screen* screen, int X, int Y) {
	for (int y = 0; y < screen->height; y++) {
		for (int x = 0; x < screen->width; x++) {
			int color = screen->blockBoard[y][x];
			if (color != 0) {
				graphicChangeLetter(screen->letter);
				graphicChangeColor(color);
				graphicDrawPoint(X + x, Y + y);
			}
		}
	}
}
void drawCurBlock(Screen* screen, int X, int Y) {
	blockDrawBlock(screen->curBlock, X + screen->curBlockX, Y + screen->curBlockY);
}
void drawShadowBlock(Screen* screen, int X, int Y) {
	blockDrawBlock(screen->shadowBlock, X + screen->curBlockX, Y + screen->shadowBlockY);
}
void drawNextBlock(Screen* screen, int X, int Y) {
	graphicChangeColor(WHITE);
	graphicMovePoint(X, Y);
	printf("·NEXT·");
	blockDrawBlock(screen->nextBlock, X, Y+1);
}
void drawHoldBlock(Screen* screen, int X, int Y) {
	graphicChangeColor(WHITE);
	graphicMovePoint(X, Y);
	printf("·HOLD·");
	if(screen->holdBlock != NULL)
		blockDrawBlock(screen->holdBlock, X, Y+1);////////////////////////////// need to modify
}
void drawFullScreen(Screen* screen, int X, int Y) {
	drawBoardFrame(screen, X, Y);
	drawBoard(screen, X + 1, Y + 1);
	drawCurBlock(screen, X + 1, Y + 1);
	drawShadowBlock(screen, X + 1, Y + 1);
	drawBlockFrame(screen, X + screen->width + 1, Y);
	drawNextBlock(screen, X + screen->width + 2, Y + 1);
	drawHoldBlock(screen, X + screen->width + 2, Y + BLOCK_HEIGHT + 2);
}

//void drawUpdatedScreen(Screen* screen, int X, int Y) {
//
//}