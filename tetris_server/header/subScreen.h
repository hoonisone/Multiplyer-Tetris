#pragma once
#include "screen.h"
#include "graphic.h"
#define SUB_SCREEN getSubScreenFunction();
typedef struct SubScreen {
	int x, y;
	Color color;
	char letter[4];

	Block* nextBlock;
	Block* holdBlock;
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