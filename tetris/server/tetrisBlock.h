#pragma once
#include <stdio.h>
#include <windows.h>

#define BLOCK_SHAPE_O 0
#define BLOCK_SHAPE_I 1
#define BLOCK_SHAPE_Z 2
#define BLOCK_SHAPE_S 3
#define BLOCK_SHAPE_L 4
#define BLOCK_SHAPE_J 5
#define BLOCK_SHAPE_T 6

typedef struct Block
{
	int x, y;
	int shape;
	int angle;
	int color;
}Block;

Block* blockCreateBlock(int color, int shape);

void blockTurnRight(Block* block);
void blockTurnLeft(Block* block);

void blockMoveTo(Block* block, int x, int y);
void blockMoveUp(Block* block);
void blockMoveDown(Block* block);
void blockMoveRight(Block* block);
void blockMoveLeft(Block* block);


int (*blockGetCurBlock(Block* block))[4];

