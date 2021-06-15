#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "block.h"
#include "math+.h"
#include "graphic.h"
#include "error.h"

void screenSetColor(Screen* screen, int color);
static ScreenFunction* createScreenFunction();
static void screenFunctionEnrollInternalMethod(ScreenFunction* sf);
void screenSetLetter(Screen* screen, char* letter);
static void screenChangeSize(Screen* screen, int width, int height);
static void screenDrawMainScreen(Screen* screen, int X, int Y);
static void screenDrawSubScreen(Screen* screen, int X, int Y);
static Block* screenNewBlock();
static void screenSetNextBlock(Screen* screen);
static void screenSetCurBlock(Screen* screen);
static void screenCurBlockMoveTo(Screen* screen, int x, int y);
static void screenCurBlockMoveUp(Screen* screen);
static void screenCurBlockMoveDown(Screen* screen);
static void screenCurBlockMoveRight(Screen* screen);
static void screenCurBlockMoveLeft(Screen* screen);
static int screenCurBlockPositionPermitCheck(Screen* screen);
static int screenCurBlockCrashCheck(Screen* screen);
static void screenInitShadowBlock(Screen* screen);
static void screenUpdateShadowBlock(Screen* screen);
static void screenUpdateShadowBlockPosition(Screen* screen);
static void screenPressCurBlock(Screen* screen);
static void screenHoldBlock(Screen* screen);
static int screenCurBlockOutOfRangeCheck(Screen* screen);
static int screenIsInRange(Screen* screen, int x, int y);
static void screenDrawFullScreen(Screen* screen, int X, int Y);
static void screenDrawBoardFrame(Screen* screen, int X, int Y);
static void screenEraseBoardFrame(Screen* screen, int X, int Y);
static void screenDrawSubFrame(Screen* screen, int X, int Y);
static void screenEraseBlockFrame(Screen* screen, int X, int Y);
static void screenDrawBoard(Screen* screen, int X, int Y);
static void screenEraseBoard(Screen* screen, int X, int Y);
static void screenDrawCurBlock(Screen* screen, int X, int Y);
static void screenEraseCurBlock(Screen* screen, int X, int Y);
static void screenDrawShadowBlock(Screen* screen, int X, int Y);
static void screenDrawNextBlock(Screen* screen, int X, int Y);
static void screenDrawHoldBlock(Screen* screen, int X, int Y);

static int colors[BLOCK_COLOR_NUM] = { LIGHT_BLUE, LIGHT_GREEN, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, BRIGHT_WHITE, LIGHT_AQUA };
static ScreenFunction* _screenFunction = NULL;

ScreenFunction* getScreenFunction() {
	if (_screenFunction == NULL) {
		_screenFunction = createScreenFunction();
	}
	return _screenFunction;
}
ScreenFunction* createScreenFunction() {
	ScreenFunction* sf = (ScreenFunction*)malloc(sizeof(ScreenFunction));
	screenFunctionEnrollInternalMethod(sf);
	return sf;
}
void screenFunctionEnrollInternalMethod(ScreenFunction* sf) {
	sf->changeSize = screenChangeSize;
	sf->drawMainScreen = screenDrawMainScreen;
	sf->drawSubScreen = screenDrawSubScreen;
	sf->newBlock = screenNewBlock;
	sf->setNextBlock = screenSetNextBlock;
	sf->setCurBlock = screenSetCurBlock;
	sf->curBlockMoveTo = screenCurBlockMoveTo;
	sf->curBlockMoveUp = screenCurBlockMoveUp;
	sf->curBlockMoveDown = screenCurBlockMoveDown;
	sf->curBlockMoveRight = screenCurBlockMoveRight;
	sf->curBlockMoveLeft = screenCurBlockMoveLeft;
	sf->curBlockPositionPermitCheck = screenCurBlockPositionPermitCheck;
	sf->curBlockCrashCheck = screenCurBlockCrashCheck;
	sf->initShadowBlock = screenInitShadowBlock;
	sf->updateShadowBlock = screenUpdateShadowBlock;
	sf->updateShadowBlockPosition = screenUpdateShadowBlockPosition;
	sf->pressCurBlock = screenPressCurBlock;
	sf->holdBlock = screenHoldBlock;
	sf->curBlockOutOfRangeCheck = screenCurBlockOutOfRangeCheck;
	sf->isInRange = screenIsInRange;
	sf->drawFullScreen = screenDrawFullScreen;
	sf->drawBoardFrame = screenDrawBoardFrame;
	sf->eraseBoardFrame = screenEraseBoardFrame;
	sf->drawSubFrame = screenDrawSubFrame;
	sf->eraseBlockFrame = screenEraseBlockFrame;
	sf->drawBoard = screenDrawBoard;
	sf->eraseBoard = screenEraseBoard;
	sf->drawCurBlock = screenDrawCurBlock;
	sf->drawShadowBlock = screenDrawShadowBlock;
	sf->drawNextBlock = screenDrawNextBlock;
	sf->drawHoldBlock = screenDrawHoldBlock;
	sf->eraseCurBlock = screenEraseCurBlock;
}

Screen* createScreen(int x, int y)
{
	Screen* object = (Screen*)malloc(sizeof(Screen));
	memset(object, 0, sizeof(Screen));	// 모든 변수를 0과 NULL로 초기화

	screenMoveTo(object, x, y);	// set screen position

	screenSetColor(object, SCREEN_DEFAULT_COLOR); // set letter shape and color	
	screenSetLetter(object, (char*)SCREEN_DEFAULT_LETTER);

	screenChangeSize(object, SCREEN_DEFAULT_WIDTH, SCREEN_DEFAULT_HEIGHT);	// set board size

	screenSetNextBlock(object);// next block must be set before setting cur block
	screenSetCurBlock(object);	// set cur boloc

	object->shadowBlock = createBlock(0, 0, 0, 0);
	screenInitShadowBlock(object);		// set shadow Block

	screenSetNextBlock(object);	// set next block

	return object;
}
void screenSetColor(Screen* screen, int color) {
	screen->color = color;
}
void screenSetLetter(Screen* screen, char* letter) {
	strcpy(screen->letter, letter);
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

void screenMoveTo(Screen* screen, int x, int y) {
	screen->x = x;
	screen->y = y;
}



void screenDrawFullScreen(Screen* screen) {
	screenDrawMainScreen(screen);
	screenDrawSubScreen(screen);
}
void screenEaraseFullScreen(Screen* screen, int x, int y) {

}
void screenDrawMainScreen(Screen* screen) {
	screenDrawBoardFrame(screen, X, Y);
	screenDrawBoard(screen, X + 1, Y + 1);
	screenDrawCurBlock(screen, X + 1, Y + 1);
	screenDrawShadowBlock(screen, X + 1, Y + 1);
}
void screenDrawSubScreen(Screen* screen, int X, int Y) {

}


//void screenEraseScreen(Screen* screen, int X, int Y) {
//
//}

//void drawUpdatedScreen(Screen* screen, int X, int Y) {
//
//}

void screenDrawFrame(Screen* screen) {
	int x = screen->x;
	int y = screen->y;
	int width = screen->width;
	screenDrawMainFrame(screen, x, y);
	screenDrawSubFrame(screen, x + width+1, y);
}
void screenDrawMainFrame(Screen* screen, int x, int y) {
	GRAPHIC->changeLetter(screen->letter);
	GRAPHIC->changeColor(screen->color);
	GRAPHIC->drawRectangle(screen->x, screen->y, screen->width + 2, screen->height + 2);
}
void screenDrawSubFrame(Screen* screen, int x, int y) {
	GRAPHIC->changeLetter(screen->letter);
	GRAPHIC->changeColor(screen->color);
	GRAPHIC->drawRectangle(screen->x+screen->width+1, screen->y, BLOCK_WIDTH + 2, screen->height + 2);

	GRAPHIC->changeColor(WHITE);
	GRAPHIC->printText(x + 1, y + 1, (char*)"·NEXT·");
	GRAPHIC->printText(x + 1, y + BLOCK_HEIGHT + 2, (char*)"·HOLD·");
}
void screenDrawMainContent() {

}
void screenDrawSubContent(Screen* screen, int x, int y) {
	screenDrawNextBlock(screen, x + 1, y + 1);
	screenDrawHoldBlock(screen, x + 1, y + BLOCK_HEIGHT + 3);
}






void screenEraseBoardFrame(Screen* screen, int X, int Y) {
	GRAPHIC->changeLetter(EMPTY_LETTER);
	GRAPHIC->changeColor(EMPTY_COLOR);
	GRAPHIC->drawRectangle(X, Y, screen->width + 2, screen->height + 2);


}

////////////////////////////////////////////////////////////////////////  Block
Block* screenNewBlock() {
	//srand(time(NULL));
	int color = rand() % BLOCK_COLOR_NUM;
	int shape = rand() % BLOCK_SHAPE_NUM;
	return createBlock(colors[color], shape);
}

void screenEraseBlockFrame(Screen* screen, int X, int Y) {
	GRAPHIC->changeLetter(EMPTY_LETTER);
	GRAPHIC->changeColor(EMPTY_COLOR);
	GRAPHIC->drawRectangle(X, Y, BLOCK_WIDTH + 2, screen->height + 2);
}

// check

int screenIsInRange(Screen* screen, int x, int y) {
	if (0 <= x && x < screen->width)
		if (0 <= y && y < screen->height)
			return 1;
	return 0;
}


// cur block
void screenSetCurBlock(Screen* screen) {
	if (screen->curBlock != NULL) {
		free(screen->curBlock);
	}
	screen->curBlock = screen->nextBlock;
	screen->nextBlock = NULL;
	screen->curBlockX = screen->width / 2 - BLOCK_WIDTH / 2;
	screen->curBlockY = 0;
	screen->floorCheck = 0; // cur블록이 바닥에 닿았다는 사실을 초기
}
void screenPressCurBlock(Screen* screen) {
	int color = screen->curBlock->color;
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (BLOCK->getShape(screen->curBlock)[y][x] == 1) {
				int relativeX = x + screen->curBlockX;
				int relativeY = y + screen->curBlockY;
				screen->blockBoard[relativeY][relativeX] = color;
			}
		}
	}
}
void screenCurBlockMoveTo(Screen* screen, int x, int y)
{
	screen->curBlockX = x;
	screen->curBlockY = y;
}
void screenCurBlockMoveUp(Screen* screen)
{
	screen->curBlockY--;
}
void screenCurBlockMoveDown(Screen* screen)
{
	screen->curBlockY++;
}
void screenCurBlockMoveRight(Screen* screen)
{
	screen->curBlockX++;
}
void screenCurBlockMoveLeft(Screen* screen)
{
	screen->curBlockX--;
}
void screenDrawCurBlock(Screen* screen, int X, int Y) {
	if (screen->curBlock != NULL) {
		BLOCK->drawBlock(screen->curBlock, X + screen->curBlockX, Y + screen->curBlockY);
	}
}
int screenCurBlockPositionPermitCheck(Screen* screen) {
	if (screenCurBlockCrashCheck(screen))
		return 0;
	if (screenCurBlockOutOfRangeCheck(screen))
		return 0;
	return 1;
}
int screenCurBlockCrashCheck(Screen* screen) {
	screen->curBlockX;
	screen->curBlockY;
	screen->width;
	screen->height;
	screen->blockBoard;

	int screenX1 = 0;
	int screenY1 = 0;
	int screenX2 = screen->width - 1;
	int screenY2 = screen->height - 1;

	int blockX1 = screen->curBlockX;
	int blockY1 = screen->curBlockY;
	int blockX2 = blockX1 + BLOCK_WIDTH - 1;
	int blockY2 = blockY1 + BLOCK_HEIGHT - 1;

	int commonX1 = greater(screenX1, blockX1);
	int commonY1 = greater(screenY1, blockY1);
	int commonX2 = smaller(screenX2, blockX2);
	int commonY2 = smaller(screenY2, blockY2);

	for (int y = commonY1; y <= commonY2; y++) {
		for (int x = commonX1; x <= commonX2; x++) {
			if (screen->blockBoard[y][x] != 0 && BLOCK->getShape(screen->curBlock)[y - commonY1][x - commonX1] != 0) {
				return 1;
			}
		}
	}
	return 0;
}
void screenEraseCurBlock(Screen* screen, int X, int Y) {
	if (screen->curBlock != NULL) {
		BLOCK->eraseBlock(screen->curBlock, X + screen->curBlockX, Y + screen->curBlockY);
	}
}
int screenCurBlockOutOfRangeCheck(Screen* screen) {
	int blockX1 = screen->curBlockX;
	int blockY1 = screen->curBlockY;

	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (BLOCK->getShape(screen->curBlock)[y][x] == 0)
				continue;
			if (!screenIsInRange(screen, x + blockX1, y + blockY1))
				return 1;
		}
	}
	return 0;
}

// shadow block
void screenInitShadowBlock(Screen* screen) {
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
	while (screenCurBlockPositionPermitCheck(screen)) {	// curBlock을 바닥 까지 내린다.
		screenCurBlockMoveDown(screen);
	}
	screenCurBlockMoveUp(screen);
	screen->floorCheck = 0;	// 임시로 내린 것이기 때문에 바닥에 닿았는지에 대한 check값 복구
	screen->shadowBlockY = screen->curBlockY;
	screenCurBlockMoveTo(screen, screen->curBlockX, originY);
}
void screenDrawShadowBlock(Screen* screen, int X, int Y) {
	if (screen->shadowBlock != NULL) {
		BLOCK->drawBlock(screen->shadowBlock, X + screen->curBlockX, Y + screen->shadowBlockY);
	}
}
void screenEraseShadowBlock(Screen* screen, int X, int Y) {
	if (screen->shadowBlock != NULL) {
		BLOCK->eraseBlock(screen->shadowBlock, X + screen->curBlockX, Y + screen->shadowBlockY);
	}
}

//////////////////////////////////////////////////////////////////////// Sub Board
void screenDrawBoard(Screen* screen, int X, int Y) {
	for (int y = 0; y < screen->height; y++) {
		for (int x = 0; x < screen->width; x++) {
			int color = screen->blockBoard[y][x];
			if (color != 0) {
				GRAPHIC->changeLetter(screen->letter);
				GRAPHIC->changeColor(color);
				GRAPHIC->drawPoint(X + x, Y + y);
			}
		}
	}
}
void screenEraseBoard(Screen* screen, int X, int Y) {
	GRAPHIC->changeLetter(EMPTY_LETTER);
	GRAPHIC->changeColor(EMPTY_COLOR);
	for (int y = 0; y < screen->height; y++) {
		for (int x = 0; x < screen->width; x++) {
			int color = screen->blockBoard[y][x];
			if (color != 0) {
				GRAPHIC->drawPoint(X + x, Y + y);
			}
		}
	}
}
// next block
void screenSetNextBlock(Screen* screen) {
	if (screen->nextBlock != NULL) {
		free(screen->nextBlock);
	}
	screen->nextBlock = screenNewBlock();
}
void screenDrawNextBlock(Screen* screen, int X, int Y) {
	if (screen->nextBlock != NULL) {
		BLOCK->drawBlock(screen->nextBlock, X, Y);
	}
}
void screenEraseNextBlock(Screen* screen, int X, int Y) {
	if (screen->nextBlock != NULL) {
		BLOCK->eraseBlock(screen->nextBlock, X, Y);
	}
}

// hold block
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
void screenDrawHoldBlock(Screen* screen, int X, int Y) {
	if (screen->holdBlock != NULL)
		BLOCK->drawBlock(screen->holdBlock, X, Y);
}
void screenEraseHoldBlock(Screen* screen, int X, int Y) {
	if (screen->holdBlock != NULL) {
		BLOCK->eraseBlock(screen->holdBlock, X, Y);
	}
}



static void subScreenSetColor(SubScreen* subScreen, int color) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	subScreen->color = color;
}
static void subScreenSetLetter(SubScreen* subScreen, char* letter) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	if (letter == NULL) {
		errorPrint("letter is null");
	}
	strcpy(subScreen->letter, letter);
}

Block* subScreenGetNextBlock(SubScreen* subScreen) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	if (subScreen->nextBlock == NULL) {
		errorPrint("next block is null");
	}
	Block* block = subScreen->nextBlock;
	subScreen->nextBlock = NULL;
	return block;
}
void subScreenSetNextBlock(SubScreen* subScreen, Block* block) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	if (block == NULL) {
		errorPrint("block is null");
	}
	BLOCK->moveTo(block, subScreen->x + 1, subScreen->y + 2);
	subScreen->nextBlock = block;
	subScreenEraseNextBlock(subScreen);
	subScreenDrawNextBlock(subScreen);
}
Block* subScreenGetHoldBlock(SubScreen* subScreen) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	if (subScreen->holdBlock == NULL) {
		errorPrint("next block is null");
	}
	Block* block = subScreen->holdBlock;
	subScreen->holdBlock = NULL;
	return block;
}
void subScreenSetHoldBlock(SubScreen* subScreen, Block* block) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	if (block == NULL) {
		errorPrint("block is null");
	}
	BLOCK->moveTo(block, subScreen->x + 1, subScreen->y + 5);
	subScreen->holdBlock = block;
	subScreenEraseHoldBlock(subScreen);
	subScreenDrawHoldBlock(subScreen);
}

void subScreenMoveTo(SubScreen* subScreen, int x, int y) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	subScreen->x = x;
	subScreen->y = y;
	subScreenDrawScreen(subScreen);
}
void subScreenDrawScreen(SubScreen* subScreen) {
	subScreenDrawFrame(subScreen);
	subScreenDrawContent(subScreen);
}
void 
void subScreenEraseFrame(SubScreen* subScreen) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	GRAPHIC->changeLetter(EMPTY_LETTER);
	GRAPHIC->changeColor(EMPTY_COLOR);
	GRAPHIC->drawRectangle(subScreen->x, subScreen->y, BLOCK_WIDTH + 2, SCREEN_DEFAULT_HEIGHT + 2);

	GRAPHIC->changeColor(WHITE);
	GRAPHIC->printText(subScreen->x + 1, subScreen->y + 1, (char*)"        ");
	GRAPHIC->printText(subScreen->x + 1, subScreen->y + BLOCK_HEIGHT + 2, (char*)"        ");
}
void subScreenDrawFrame(SubScreen* subScreen) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	GRAPHIC->changeLetter(subScreen->letter);
	GRAPHIC->changeColor(subScreen->color);
	GRAPHIC->drawRectangle(subScreen->x, subScreen->y, BLOCK_WIDTH + 2, SCREEN_DEFAULT_HEIGHT + 2);

	GRAPHIC->changeColor(WHITE);
	GRAPHIC->printText(subScreen->x + 1, subScreen->y + 1, (char*)"·NEXT·");
	GRAPHIC->printText(subScreen->x + 1, subScreen->y + BLOCK_HEIGHT + 2, (char*)"·HOLD·");
}
void subScreenEraseContent(SubScreen* subScreen) {
	subScreenEraseNextBlock(subScreen);
	subScreenEraseHoldBlock(subScreen);
}
void subScreenDrawContent(SubScreen* subScreen) {
	subScreenEraseContent(subScreen);
	subScreenDrawNextBlock(subScreen);
	subScreenDrawHoldBlock(subScreen);
}


static void subScreenEraseNextBlock(SubScreen* subScreen) {
	static Block* block = subScreen->nextBlock;
	if (block != NULL) {
		BLOCK->eraseBlock(block);
	}
}
static void subScreenDrawNextBlock(SubScreen* subScreen) {
	static Block* block = subScreen->nextBlock;
	if (block != NULL) {
		BLOCK->drawBlock(block);
	}
}
static void subScreenEraseHoldBlock(SubScreen* subScreen) {
	static Block* block = subScreen->holdBlock;
	if (block != NULL) {
		BLOCK->eraseBlock(block);
	}
}
static void subScreenDrawHoldBlock(SubScreen* subScreen) {
	static Block* block = subScreen->holdBlock;
	if (block != NULL) {
		BLOCK->drawBlock(block);
	}
}

