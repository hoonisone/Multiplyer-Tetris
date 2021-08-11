//#include "error.h"
//#include "block.h"
//#include "graphic.h"
//#include "subScreen.h"
//#include "mainScreen.h"
//
//#define SUB_SCREEN_DEFAULT_LETTER "＝"
//#define SUB_SCREEN_DEFAULT_COLOR WHITE
//
//// defaul function
//static SubScreen* subScreenCreate(int x, int y, int width, int height, Block* nextBlock);
//static Block* subScreenChangeNextBlock(SubScreen* subScreen, Block* newBlock);
//
//// external application function (conduct many works for keep certain state)
//static Block* subScreenTakeNextBlock(SubScreen* subScreen);
//static void subScreenSetNextBlock(SubScreen* subScreen, Block* block);
//static Block* subScreenTakeHoldBlock(SubScreen* subScreen);
//static void subScreenSetHoldBlock(SubScreen* subScreen, Block* block);
//static void subScreenMoveTo(SubScreen* subScreen, int x, int y);
//
//// internal material function(conduct only one work)
//static void subScreenSetColor(SubScreen* subScreen, int color);
//static void subScreenSetLetter(SubScreen* subScreen, char* letter);
//static void subScreenDrawScreen(SubScreen* subScreen);
//static void subScreenEraseScreen(SubScreen* subScreen);
//static void subScreenEraseFrame(SubScreen* subScreen);
//static void subScreenDrawFrame(SubScreen* subScreen);
//static void subScreenEraseContent(SubScreen* subScreen);
//static void subScreenDrawContent(SubScreen* subScreen);
//static void subScreenEraseNextBlock(SubScreen* subScreen);
//static void subScreenDrawNextBlock(SubScreen* subScreen);
//static void subScreenEraseHoldBlock(SubScreen* subScreen);
//static void subScreenDrawHoldBlock(SubScreen* subScreen);
//static void subScreenDelete(SubScreen* subScreen);
//
//// defaul function
//SubScreenFunction* getSubScreenFunction() {
//	static SubScreenFunction* object = NULL;
//	if (object == NULL) {
//		object = (SubScreenFunction*)malloc(sizeof(SubScreenFunction));
//		object->create = subScreenCreate;
//		object->changeNextBlock = subScreenChangeNextBlock;
//		object->moveTo = subScreenMoveTo;
//		object->del = subScreenDelete;
//	}
//	return object;
//}
//
//SubScreen* subScreenCreate(int x, int y, int width, int height, Block* nextBlock) {
//	SubScreen* object = (SubScreen*)malloc(sizeof(SubScreen));
//	memset(object, 0, sizeof(SubScreen));
//	subScreenMoveTo(object, x, y);
//	object->width = width;
//	object->height = height;
//	subScreenSetColor(object, SUB_SCREEN_DEFAULT_COLOR);
//	subScreenSetLetter(object, (char*)SUB_SCREEN_DEFAULT_LETTER);
//	subScreenSetNextBlock(object, nextBlock);
//	subScreenDrawNextBlock(object);
//	return object;
//}
//
//static Block* subScreenChangeNextBlock(SubScreen* subScreen, Block* newBlock) {
//	subScreenEraseNextBlock(subScreen);
//	Block* block = subScreenTakeNextBlock(subScreen);
//	subScreenSetNextBlock(subScreen, newBlock);
//	subScreenDrawNextBlock(subScreen);
//	return block;
//}
//
//// external application function (conduct many works for keep certain state)
//static Block* subScreenTakeNextBlock(SubScreen* subScreen) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	if (subScreen->nextBlock == NULL) {
//		errorPrint("next block is null");
//	}
//	Block* block = subScreen->nextBlock;
//	subScreen->nextBlock = NULL;
//	return block;
//}
//static void subScreenSetNextBlock(SubScreen* subScreen, Block* block) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	if (block == NULL) {
//		errorPrint("block is null");
//	}
//	BLOCK->moveTo(block, subScreen->x + 1, subScreen->y + 2);
//	subScreen->nextBlock = block;
//}
//static Block* subScreenTakeHoldBlock(SubScreen* subScreen) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	if (subScreen->holdBlock == NULL) {
//		errorPrint("next block is null");
//	}
//	Block* block = subScreen->holdBlock;
//	subScreen->holdBlock = NULL;
//	return block;
//}
//static void subScreenSetHoldBlock(SubScreen* subScreen, Block* block) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	if (block == NULL) {
//		errorPrint("block is null");
//	}
//	BLOCK->moveTo(block, subScreen->x + 1, subScreen->y + 7);
//	subScreen->holdBlock = block;
//}
//
//static void subScreenMoveTo(SubScreen* subScreen, int x, int y) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	subScreen->x = x;
//	subScreen->y = y;
//	subScreenEraseScreen(subScreen);
//	subScreenDrawScreen(subScreen);
//}
//
//// internal material function(conduct only one work)
//static void subScreenSetColor(SubScreen* subScreen, int color) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	subScreen->color = color;
//	subScreenDrawFrame(subScreen);
//}
//static void subScreenSetLetter(SubScreen* subScreen, char* letter) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	if (letter == NULL) {
//		errorPrint("letter is null");
//	}
//	strcpy(subScreen->letter, letter);
//	subScreenDrawFrame(subScreen);
//}
//
//static void subScreenDrawScreen(SubScreen* subScreen) {
//	subScreenDrawFrame(subScreen);
//	subScreenDrawContent(subScreen);
//}
//static void subScreenEraseScreen(SubScreen* subScreen) {
//	subScreenEraseFrame(subScreen);
//	subScreenEraseContent(subScreen);
//}
//
//static void subScreenEraseFrame(SubScreen* subScreen) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	GRAPHIC->setLetter(EMPTY_LETTER);
//	GRAPHIC->setColor(EMPTY_COLOR);
//	GRAPHIC->drawRectangle(subScreen->x, subScreen->y, BLOCK_WIDTH + 2, SCREEN_DEFAULT_HEIGHT + 2);
//
//	GRAPHIC->setColor(WHITE);
//	GRAPHIC->printText(subScreen->x + 1, subScreen->y + 1, (char*)"        ");
//	GRAPHIC->printText(subScreen->x + 1, subScreen->y + BLOCK_HEIGHT + 2, (char*)"        ");
//}
//static void subScreenDrawFrame(SubScreen* subScreen) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	GRAPHIC->setLetter(subScreen->letter);
//	GRAPHIC->setColor(subScreen->color);
//	GRAPHIC->drawRectangle(subScreen->x, subScreen->y, subScreen->width, subScreen->height);
//
//	GRAPHIC->setColor(WHITE);
//	GRAPHIC->printText(subScreen->x + 1, subScreen->y + 1, (char*)"，NEXT，");
//	GRAPHIC->printText(subScreen->x + 1, subScreen->y + 1 + BLOCK_HEIGHT+1, (char*)"，HOLD，");
//}
//static void subScreenEraseContent(SubScreen* subScreen) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	subScreenEraseNextBlock(subScreen);
//	subScreenEraseHoldBlock(subScreen);
//}
//static void subScreenDrawContent(SubScreen* subScreen) {
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	subScreenDrawNextBlock(subScreen);
//	subScreenDrawHoldBlock(subScreen);
//}
//
//static void subScreenEraseNextBlock(SubScreen* subScreen) {
//	Block* block = subScreen->nextBlock;
//	if (block != NULL) {
//		BLOCK->erase(block);
//	}
//}
//static void subScreenDrawNextBlock(SubScreen* subScreen) {
//	Block* block = subScreen->nextBlock;
//	if (block != NULL) {
//		BLOCK->draw(block);
//	}
//}
//static void subScreenEraseHoldBlock(SubScreen* subScreen) {
//	Block* block = subScreen->holdBlock;
//	if (block != NULL) {
//		BLOCK->erase(block);
//	}
//}
//static void subScreenDrawHoldBlock(SubScreen* subScreen) {
//	Block* block = subScreen->holdBlock;
//	if (block != NULL) {
//		BLOCK->draw(block);
//	}
//}
//static void subScreenDelete(SubScreen* subScreen) {
//	Block* block = NULL;
//	if (subScreen == NULL) {
//		errorPrint("subScreen is null");
//	}
//	subScreenEraseScreen(subScreen);
//
//	block = subScreen->holdBlock;
//	if (block != NULL) {
//		free(block);
//	}
//
//	block = subScreen->holdBlock;
//	if (block != NULL) {
//		free(block);
//	}
//	free(subScreen);
//}