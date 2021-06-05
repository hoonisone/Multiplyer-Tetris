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

#define BLOCK_SHAPE_NUM 7
#define BLOCK_ANGLE_NUM 4
#define BLOCK_WIDTH 4
#define BLOCK_HEIGHT 4

typedef struct Block
{
	int shape;
	int angle;
	int color;
}Block;

Block* blockCreateBlock(int color, int shape);

void blockTurnRight(Block* block);
void blockTurnLeft(Block* block);

//void blockMoveTo(Block* block, int x, int y);
//void blockMoveUp(Block* block);
//void blockMoveDown(Block* block);
//void blockMoveRight(Block* block);
//void blockMoveLeft(Block* block);


int (*blockGetShape(Block* block))[4];

