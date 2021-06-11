#include <stdio.h>
#include <windows.h>
#include "tetrisBlock.h"
#include "graphic.h"

static int BLOCK_SHAPE[7][4][4][4] = {
{{{0,0,0,0}, //O
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}}},
{{{0,0,0,0}, //I
  {0,0,0,0},
  {1,1,1,1},
  {0,0,0,0}},
 {{0,1,0,0},
  {0,1,0,0},
  {0,1,0,0},
  {0,1,0,0}},
 {{0,0,0,0},
  {0,0,0,0},
  {1,1,1,1},
  {0,0,0,0}},
 {{0,1,0,0},
  {0,1,0,0},
  {0,1,0,0},
  {0,1,0,0}}},
{{{0,0,0,0}, //Z
  {1,1,0,0},
  {0,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,0,1,0},
  {0,1,1,0},
  {0,1,0,0}},
 {{0,0,0,0},
  {1,1,0,0},
  {0,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,0,1,0},
  {0,1,1,0},
  {0,1,0,0}}},
{{{0,0,0,0}, //S
  {0,1,1,0},
  {1,1,0,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {1,0,0,0},
  {1,1,0,0},
  {0,1,0,0}},
 {{0,0,0,0},
  {0,1,1,0},
  {1,1,0,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {1,0,0,0},
  {1,1,0,0},
  {0,1,0,0}}},
{{{0,0,0,0}, //L
  {0,0,1,0},
  {1,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {1,1,0,0},
  {0,1,0,0},
  {0,1,0,0}},
 {{0,0,0,0},
  {0,0,0,0},
  {1,1,1,0},
  {1,0,0,0}},
 {{0,0,0,0},
  {0,1,0,0},
  {0,1,0,0},
  {0,1,1,0}}},
{{{0,0,0,0}, //J
  {1,0,0,0},
  {1,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,0,0},
  {0,1,0,0},
  {1,1,0,0}},
 {{0,0,0,0},
  {0,0,0,0},
  {1,1,1,0},
  {0,0,1,0}},
 {{0,0,0,0},
  {0,1,1,0},
  {0,1,0,0},
  {0,1,0,0}}},
{{{0,0,0,0}, //T
  {0,1,0,0},
  {1,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,0,0},
  {0,1,1,0},
  {0,1,0,0}},
 {{0,0,0,0},
  {0,0,0,0},
  {1,1,1,0},
  {0,1,0,0}},
 {{0,0,0,0},
  {0,1,0,0},
  {1,1,0,0},
  {0,1,0,0}}}
};

Block* blockCreateBlock(int color, int shape)
{
	Block* newBlock = (Block*)malloc(sizeof(Block));
	newBlock->shape = shape;
	newBlock->angle = 0;
	newBlock->color = color;
	strcpy(newBlock->letter, BLOCK_DEFAULT_LETTER);
	return newBlock;
}

void blockTurnRight(Block* block){
	block->angle = (block->angle + 1) % BLOCK_ANGLE_NUM;
}
void blockTurnLeft(Block* block){
	block->angle = (block->angle + (BLOCK_ANGLE_NUM-1)) % BLOCK_ANGLE_NUM;
}

int(*blockGetShape(Block* block))[BLOCK_ANGLE_NUM]
{
	return BLOCK_SHAPE[block->shape][block->angle];
}

void blockDrawBlock(Block * block, int X, int Y) {
	
	graphicManager->changeColor(block->color);
	graphicManager->changeLetter(block->letter);
	
	int (*shape)[BLOCK_ANGLE_NUM] = blockGetShape(block);
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (shape[y][x] == 1) {
				graphicManager->drawPoint(X + x, Y + y);
			}
		}
	}
}