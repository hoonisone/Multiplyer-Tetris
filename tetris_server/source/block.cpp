#include <stdio.h>
#include <windows.h>
#include "block.h"
#include "graphic.h"
#include "error.h"

static Color BLOCK_SHAPE[7][4][4][4] = {// 블록 데이터
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
static BlockFunction* createBlockFunction();

static Block* blockCreate(int x, int y, int color, int shape);
static Block* blockCopy(Block* block);
static BlockShape blockGetShape(Block* block);
static void blockSetShape(Block* block, int shape);
static void blockSetAngle(Block* block, int angle);
static void blockSetColor(Block* block, Color color);
static void blockSetLetter(Block* block, char* letter);

static void blockTurnRight(Block* block);
static void blockTurnLeft(Block* block);
static void blockMoveTo(Block* block, int x, int y);
static void blockMoveUp(Block* block);
static void blockMoveDown(Block* block);
static void blockMoveRight(Block* block);
static void blockMoveLeft(Block* block);
static void blockDrawBlock(Block* block);
static void blockDelete(Block* block);

// block function object
BlockFunction* getBlockFunction() {// return singleton block function object
	static BlockFunction* blockFunction = createBlockFunction();
	return blockFunction;
}
static BlockFunction* createBlockFunction() {// block function object constructor
	BlockFunction* bf = (BlockFunction*)malloc(sizeof(BlockFunction));
	bf->create = blockCreate;
	bf->copy = blockCopy;
	// get set
	bf->getShape = blockGetShape;
	bf->setShape = blockSetShape;
	bf->setAngle = blockSetAngle;
	bf->setColor = blockSetColor;
	bf->setLetter = blockSetLetter;

	// contoll
	bf->turnRight = blockTurnRight;
	bf->turnLeft = blockTurnLeft;
	bf->moveTo = blockMoveTo;
	bf->moveUp = blockMoveUp;
	bf->moveDown = blockMoveDown;
	bf->moveRight = blockMoveRight;
	bf->moveLeft = blockMoveLeft;
	// draw
	bf->drawBlock = blockDrawBlock;
	bf->del = blockDelete;
	return bf;
}

// internal method of block object
static Block* blockCreate(int x, int y, int color, int shape)	// block constructor
{
	Block* object = (Block*)malloc(sizeof(Block));
	object->x = x;
	object->y = y;
	object->color = color;
	object->shape = shape;
	object->angle = 0;
	strcpy(object->letter, BLOCK_DEFAULT_LETTER);
	return object;
}
static Block* blockCopy(Block* block) {
	Block* copyBlock = blockCreate(0, 0, 0, 0);
	memcpy(copyBlock, block, sizeof(Block));
	return copyBlock;
}

// getter setter
static BlockShape blockGetShape(Block* block)
{
	return BLOCK_SHAPE[block->shape][block->angle];
}
static void blockSetShape(Block* block, int shape) {
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	block->shape = shape;
}
static void blockSetAngle(Block* block, int angle) {
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	block->angle = angle % BLOCK_ANGLE_NUM;
}
static void blockSetColor(Block* block, Color color) {
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	block->color = color;
}
static void blockSetLetter(Block* block, char* letter) {
	strcpy(block->letter, letter);
}

// lotate controll
static void blockTurnRight(Block* block){
	block->angle = (block->angle + 1) % BLOCK_ANGLE_NUM;
}
static void blockTurnLeft(Block* block){
	block->angle = (block->angle + (BLOCK_ANGLE_NUM-1)) % BLOCK_ANGLE_NUM;
}

// move controll
static void blockMoveTo(Block* block, int x, int y) {
	block->x = x;
	block->y = y;
}
static void blockMoveUp(Block* block) {
	block->y--;
}
static void blockMoveDown(Block* block) {
	block->y++;
}
static void blockMoveRight(Block* block) {
	block->x++;
}
static void blockMoveLeft(Block* block) {
	block->x--;
}

static void blockDrawBlock(Block * block) {
	GRAPHIC->changeColor(block->color);
	GRAPHIC->changeLetter(block->letter);
	
	BlockShape shape = blockGetShape(block);
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (shape[y][x] == 1) {
				GRAPHIC->drawPoint(block->x + x, block->y + y);
			}
		}
	}
}
static void blockDelete(Block* block) {
	GRAPHIC->changeColor(EMPTY_COLOR);
	GRAPHIC->changeLetter((char*)EMPTY_LETTER);
	int(*shape)[BLOCK_ANGLE_NUM] = blockGetShape(block);
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (shape[y][x] == 1) {
				GRAPHIC->drawPoint(block->x + x, block->y + y);
			}
		}
	}
}