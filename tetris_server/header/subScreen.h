#pragma once
#include "screen.h"
#define SUB_SCREEN getSubScreenFunction();
typedef struct SubScreen {
	int x, y;
	int color;
	char letter[4];

	Block* nextBlock, * holdBlock;
}SubScreen;

typedef struct SubScreenFunction {
	SubScreen* (*create)(int x, int y);
	Block* (*detNextBlock)(SubScreen* subScreen);
	void (*setNextBlock)(SubScreen* subScreen, Block* block);
	Block* (*getHoldBlock)(SubScreen* subScreen);
	void (*setHoldBlock)(SubScreen* subScreen, Block* block);
	void (*moveTo)(SubScreen* subScreen, int x, int y);
	void (*del)(SubScreen* subScreen);
};

//default function
SubScreenFunction* getSubScreenFunction();