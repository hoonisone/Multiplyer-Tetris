#include <stdio.h>
#include <windows.h>
#include "block.h"
#include "graphic.h"

static int BLOCK_SHAPE[7][4][4][4] = {// 블록 데이터
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
static BlockFunction* _blockFunction = NULL; // 함수 관리 객체(싱글톤)

static int(*blockGetShape(Block* block))[BLOCK_ANGLE_NUM];
static void blockSetLetter(Block* block, char* letter);
static void blockTurnRight(Block* block);
static void blockTurnLeft(Block* block);
static void blockMoveTo(Block* block, int x, int y);
static void blockMoveUp(Block* block);
static void blockMoveDown(Block* block);
static void blockMoveRight(Block* block);
static void blockMoveLeft(Block* block);
static void blockDrawBlock(Block* block);
static void blockEraseBlock(Block* block);


// block function object
BlockFunction* getBlockFunction() {// return singleton block function object
	if (_blockFunction == NULL) {
		_blockFunction = createBlockFunction();
	}
	return _blockFunction;
}
BlockFunction* createBlockFunction() {// block function object constructor
	BlockFunction* bf = (BlockFunction*)malloc(sizeof(BlockFunction));
	blockFunctionFillInternalMethod(bf);
	return bf;
}
static void blockFunctionFillInternalMethod(BlockFunction* bf) {// 함수 관리 객체에 함수 등록
	// get set
	bf->getShape = blockGetShape;
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
	bf->eraseBlock = blockEraseBlock;
}	  

// internal method of block object
Block* createBlock(int x, int y, int color, int shape)	// block constructor
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

// getter setter
int(*blockGetShape(Block* block))[BLOCK_ANGLE_NUM]
{
	return BLOCK_SHAPE[block->shape][block->angle];
}
void blockSetLetter(Block* block, char* letter) {
	strcpy(block->letter, letter);
}


// lotate controll
void blockTurnRight(Block* block){
	block->angle = (block->angle + 1) % BLOCK_ANGLE_NUM;
}
void blockTurnLeft(Block* block){
	block->angle = (block->angle + (BLOCK_ANGLE_NUM-1)) % BLOCK_ANGLE_NUM;
}

// move controll
void blockMoveTo(Block* block, int x, int y) {
	block->x = x;
	block->y = y;
}
void blockMoveUp(Block* block) {
	block->y--;
}
void blockMoveDown(Block* block) {
	block->y++;
}
void blockMoveRight(Block* block) {
	block->x++;
}
void blockMoveLeft(Block* block) {
	block->x--;
}

void blockDrawBlock(Block * block) {
	GRAPHIC->changeColor(block->color);
	GRAPHIC->changeLetter(block->letter);
	
	int (*shape)[BLOCK_ANGLE_NUM] = blockGetShape(block);
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (shape[y][x] == 1) {
				GRAPHIC->drawPoint(block->x + x, block->y + y);
			}
		}
	}
}
void blockEraseBlock(Block* block) {
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

