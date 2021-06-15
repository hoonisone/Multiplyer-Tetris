#include "subScreen.h"
#include "error.h"

// defaul function
static SubScreen* subScreenCreate(int x, int y);
static SubScreenFunction* createSubScreenFunction();
static void subScreenFunctionFillMethod(SubScreenFunction* object);

// external application function (conduct many works for keep certain state)
static Block* subScreenGetNextBlock(SubScreen* subScreen);
static void subScreenSetNextBlock(SubScreen* subScreen, Block* block);
static Block* subScreenGetHoldBlock(SubScreen* subScreen);
static void subScreenSetHoldBlock(SubScreen* subScreen, Block* block);
static void subScreenMoveTo(SubScreen* subScreen, int x, int y);

// internal material function(conduct only one work)
static void subScreenSetColor(SubScreen* subScreen, int color);
static void subScreenSetLetter(SubScreen* subScreen, char* letter);
static void subScreenDrawScreen(SubScreen* subScreen);
static void subScreenEraseScreen(SubScreen* subScreen);
static void subScreenEraseFrame(SubScreen* subScreen);
static void subScreenDrawFrame(SubScreen* subScreen);
static void subScreenEraseContent(SubScreen* subScreen);
static void subScreenDrawContent(SubScreen* subScreen);
static void subScreenEraseNextBlock(SubScreen* subScreen);
static void subScreenDrawNextBlock(SubScreen* subScreen);
static void subScreenEraseHoldBlock(SubScreen* subScreen);
static void subScreenDrawHoldBlock(SubScreen* subScreen);
static void subScreenDelete(SubScreen* subScreen);

// defaul function
SubScreen* subScreenCreate(int x, int y) {
	SubScreen* object = (SubScreen*)malloc(sizeof(SubScreen));
	memcpy(object, 0, sizeof(SubScreen));
	subScreenMoveTo(object, x, y);
	subScreenSetColor(object, SCREEN_DEFAULT_COLOR);
	subScreenSetLetter(object, (char*)SCREEN_DEFAULT_LETTER);
	return object;
}
SubScreenFunction* getSubScreenFunction() {
	static SubScreenFunction* _subScreenFunction = createSubScreenFunction();
	return _subScreenFunction;
}
SubScreenFunction* createSubScreenFunction() {
	SubScreenFunction* object = (SubScreenFunction*)malloc(sizeof(SubScreenFunction));
	subScreenFunctionFillMethod(object);
	return object;
}
void subScreenFunctionFillMethod(SubScreenFunction* object) {
	object->create = subScreenCreate;
	object->detNextBlock = subScreenGetNextBlock;
	object->setNextBlock = subScreenSetNextBlock;
	object->getHoldBlock = subScreenGetHoldBlock;
	object->setHoldBlock = subScreenSetHoldBlock;
	object->moveTo = subScreenMoveTo;
	object->del = subScreenDelete;
}

// external application function (conduct many works for keep certain state)
static Block* subScreenGetNextBlock(SubScreen* subScreen) {
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
static void subScreenSetNextBlock(SubScreen* subScreen, Block* block) {
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
static Block* subScreenGetHoldBlock(SubScreen* subScreen) {
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
static void subScreenSetHoldBlock(SubScreen* subScreen, Block* block) {
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
static void subScreenMoveTo(SubScreen* subScreen, int x, int y) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	subScreen->x = x;
	subScreen->y = y;
	subScreenEraseScreen(subScreen);
	subScreenDrawScreen(subScreen);
}

// internal material function(conduct only one work)
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

static void subScreenDrawScreen(SubScreen* subScreen) {
	subScreenDrawFrame(subScreen);
	subScreenDrawContent(subScreen);
}
static void subScreenEraseScreen(SubScreen* subScreen) {
	subScreenEraseFrame(subScreen);
	subScreenEraseContent(subScreen);
}

static void subScreenEraseFrame(SubScreen* subScreen) {
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
static void subScreenDrawFrame(SubScreen* subScreen) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	GRAPHIC->changeLetter(subScreen->letter);
	GRAPHIC->changeColor(subScreen->color);
	GRAPHIC->drawRectangle(subScreen->x, subScreen->y, BLOCK_WIDTH + 2, SCREEN_DEFAULT_HEIGHT + 2);

	GRAPHIC->changeColor(WHITE);
	GRAPHIC->printText(subScreen->x + 1, subScreen->y + 1, (char*)"，NEXT，");
	GRAPHIC->printText(subScreen->x + 1, subScreen->y + BLOCK_HEIGHT + 2, (char*)"，HOLD，");
}
static void subScreenEraseContent(SubScreen* subScreen) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	subScreenEraseNextBlock(subScreen);
	subScreenEraseHoldBlock(subScreen);
}
static void subScreenDrawContent(SubScreen* subScreen) {
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	subScreenDrawNextBlock(subScreen);
	subScreenDrawHoldBlock(subScreen);
}

static void subScreenEraseNextBlock(SubScreen* subScreen) {
	Block* block = subScreen->nextBlock;
	if (block != NULL) {
		BLOCK->eraseBlock(block);
	}
}
static void subScreenDrawNextBlock(SubScreen* subScreen) {
	Block* block = subScreen->nextBlock;
	if (block != NULL) {
		BLOCK->drawBlock(block);
	}
}
static void subScreenEraseHoldBlock(SubScreen* subScreen) {
	Block* block = subScreen->holdBlock;
	if (block != NULL) {
		BLOCK->eraseBlock(block);
	}
}
static void subScreenDrawHoldBlock(SubScreen* subScreen) {
	Block* block = subScreen->holdBlock;
	if (block != NULL) {
		BLOCK->drawBlock(block);
	}
}
static void subScreenDelete(SubScreen* subScreen) {
	Block* block = NULL;
	if (subScreen == NULL) {
		errorPrint("subScreen is null");
	}
	subScreenEraseScreen(subScreen);

	block = subScreen->holdBlock;
	if (block != NULL) {
		free(block);
	}

	block = subScreen->holdBlock;
	if (block != NULL) {
		free(block);
	}
	free(subScreen);
}