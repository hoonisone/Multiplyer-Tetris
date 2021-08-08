#pragma once
#include <stdio.h>
#include <windows.h>
#include "Pencil.h"

#define BLOCK_SHAPE_O 0
#define BLOCK_SHAPE_I 1
#define BLOCK_SHAPE_Z 2
#define BLOCK_SHAPE_S 3
#define BLOCK_SHAPE_L 4
#define BLOCK_SHAPE_J 5
#define BLOCK_SHAPE_T 6

#define BLOCK_SHAPE_NUM 7
#define BLOCK_ANGLE_NUM 4
#define BLOCK_WIDTH 4
#define BLOCK_HEIGHT 4
#define BLOCK_DEFAULT_LETTER "■"
#define BLOCK_SHAPE_LETTER "□"
#define BLOCK_COLOR_NUM 7
#define BLOCK getBlockFunction()

typedef Color (*BlockShape)[BLOCK_HEIGHT];

typedef struct Block	//구조체 Block 정의
{
	int x, y;
	int shape, angle, color;
	char letter[4]; // unicode(3bype) + null(1byte)
}Block;

typedef struct BlockFunction {	//구조체 BlockFunction 정의
	Block* (*create)(int x, int y, int color, int shape, int angle);
	Block* (*createRandomBlock)();
	Block* (*copy)(Block* block);
	// getter setter
	BlockShape (*getShape)(Block* block);
	void (*setShape)(Block* block, int shape);
	void (*setAngle)(Block* block, int angle);
	void (*setColor)(Block* block, Color color);
	void (*setLetter)(Block* block, char* letter);

	// lotate controll
	void (*turnRight)(Block* block);
	void (*turnLeft)(Block* block);
	
	// move controll
	void (*moveTo)(Block* block, int x, int y);
	void (*moveUp)(Block* block);
	void (*moveDown)(Block* block);
	void (*moveRight)(Block* block);
	void (*moveLeft)(Block* block);
	
	// draw
	void (*draw)(Block* block);
	void (*erase)(Block* block);

	int (*rangeCheck)(Block* block, int x, int y);
}BlockFunction;

BlockFunction* getBlockFunction();