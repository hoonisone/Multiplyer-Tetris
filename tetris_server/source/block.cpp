#include <stdio.h>
#include <windows.h>
#include "block.h"		//��� ����ü ����, ��Ʈ���� ��� ��� ����, ��� ���� �����ڵ� ����
#include "graphic.h"	//��� �׷��� ���� �������
#include "error.h"		//���� ���� �������
#include "random.h"		//���� �������

//�Լ� ���� �κ�
static BlockFunction* createBlockFunction();
static Block* blockCreate(int x, int y, int color, int shape, int angle);
static Block* blockCreateRandomBlock();
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
static void blockErase(Block* block);
static int blockRangeCheck(Block* block, int x, int y);

static Color BLOCK_SHAPE[7][4][4][4] = {// ��� ������, [7���][4����][����ũ��][����ũ��]
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
  {1,1,1,1},
  {0,0,0,0},
  {0,0,0,0}},
 {{0,1,0,0},
  {0,1,0,0},
  {0,1,0,0},
  {0,1,0,0}},
 {{0,0,0,0},
  {1,1,1,1},
  {0,0,0,0},
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
  {0,1,0,0},
  {0,1,1,0},
  {0,0,1,0}},
 {{0,0,0,0},
  {0,1,1,0},
  {1,1,0,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,0,0},
  {0,1,1,0},
  {0,0,1,0}}},
{{{0,1,0,0}, //L
  {0,1,0,0},
  {0,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,1,1},
  {0,1,0,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,1,0},
  {0,0,1,0},
  {0,0,1,0}},
 {{0,0,0,0},
  {0,0,1,0},
  {1,1,1,0},
  {0,0,0,0}}},
{{{0,0,1,0}, //J
  {0,0,1,0},
  {0,1,1,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,0,0},
  {0,1,1,1},
  {0,0,0,0}},
 {{0,0,0,0},
  {0,1,1,0},
  {0,1,0,0},
  {0,1,0,0}},
 {{0,0,0,0},
  {1,1,1,0},
  {0,0,1,0},
  {0,0,0,0}}},
{{{0,1,0,0}, //T
  {1,1,1,0},
  {0,0,0,0},
  {0,0,0,0}},
 {{0,1,0,0},
  {0,1,1,0},
  {0,1,0,0},
  {0,0,0,0}},
 {{0,0,0,0},
  {1,1,1,0},
  {0,1,0,0},
  {0,0,0,0}},
 {{0,1,0,0},
  {1,1,0,0},
  {0,1,0,0},
  {0,0,0,0}}}
};
static int colors[BLOCK_COLOR_NUM] = { LIGHT_BLUE, LIGHT_GREEN, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE, LIGHT_AQUA };
//�� ������ �����ϴ� int�� colors�迭 ���� �� ������ graphic.h���� ���������� ���ǵǾ�����
// block function object	��� �Լ� ��ü
BlockFunction* getBlockFunction() {// return singleton block function object	�̱��� ��� �Լ� ��ü ��ȯ
	static BlockFunction* blockFunction = createBlockFunction();
	return blockFunction;
}

static BlockFunction* createBlockFunction() {// block function object constructor	��� �Լ� ��ü ������
	BlockFunction* bf = (BlockFunction*)malloc(sizeof(BlockFunction));	//bf�����Ҵ�
	//����ü ������� �� �Լ��鿡 �Ҵ�
	bf->create = blockCreate;							//����� x,y��ǥ, ���, ����, ������ ����
	bf->createRandomBlock = blockCreateRandomBlock;		//����� ���, ����, ������ �������� �Ҵ��Ŵ
	bf->copy = blockCopy;								//����� �����͸� ������

	// get set
	bf->getShape = blockGetShape;
	bf->setShape = blockSetShape;
	bf->setAngle = blockSetAngle;
	bf->setColor = blockSetColor;
	bf->setLetter = blockSetLetter;

	// contoll
	bf->turnRight = blockTurnRight;						//����� ���������� 90�� ȸ��
	bf->turnLeft = blockTurnLeft;						//����� �������� 90�� ȸ��
	bf->moveTo = blockMoveTo;							//����� ������� ���� ���ڷ� ���� x,y��ǥ�� �ű�
	bf->moveUp = blockMoveUp;							//����� �� ĭ ����
	bf->moveDown = blockMoveDown;						//����� �� ĭ �Ʒ���
	bf->moveRight = blockMoveRight;						//����� �� ĭ ����������
	bf->moveLeft = blockMoveLeft;						//����� �� ĭ ��������
	// draw
	bf->draw = blockDrawBlock;							//�Ҵ�� ������ ����� �׸�
	bf->erase = blockErase;								//����� ����

	bf->rangeCheck = blockRangeCheck;					//����� ������ üũ��
	return bf;											//bf��ȯ
}

// internal method of block object	��� ��ü�� ���� �޼ҵ�
static Block* blockCreate(int x, int y, int color, int shape, int angle)	// block constructor	��� ������
{
	Block* object = (Block*)malloc(sizeof(Block));	//object�����Ҵ�
	object->x = x;									//��� ��������� x��ǥ
	object->y = y;									//��� ��������� y��ǥ
	blockSetColor(object, color);					//
	object->shape = shape%BLOCK_SHAPE_NUM;			//��� ���
	object->angle = angle%BLOCK_ANGLE_NUM;			//��� ����
	strcpy(object->letter, BLOCK_DEFAULT_LETTER);	//��� ���ڿ�(�����ڵ�+�ι���) ����
	return object;									//object��ȯ
}
static Block* blockCreateRandomBlock() {				//���� ������� ����, ���� ���, ����, ������ �������� �Ҵ���� ��ȯ
	int shape = RANDOM->getValue() % BLOCK_SHAPE_NUM;	//��� ��� ���� �Ҵ�
	int angle = RANDOM->getValue() % BLOCK_ANGLE_NUM;	//��� ���� ���� �Ҵ�
	Color color = RANDOM->getValue() % BLOCK_COLOR_NUM;	//��� ���� ���� �Ҵ�
	return BLOCK->create(0, 0, color, shape, angle);	//���, ����, ������ �Ҵ�� ��� ��ȯ
}
static Block* blockCopy(Block* block) {				//���� ������
	Block* copyBlock = blockCreate(0, 0, 0, 0, 0);	//copyBlock���� ����
	memcpy(copyBlock, block, sizeof(Block));		//copyBlock������ ���� ���ڰ����� memcpy�޸𸮺��� 
	return copyBlock;								//copyBlock ��ȯ
}

// getter setter
static BlockShape blockGetShape(Block* block)		//��� ���+���� �Լ�
{
	return BLOCK_SHAPE[block->shape][block->angle];	//��� ���, ���� ��ȯ
}
static void blockSetShape(Block* block, int shape) {	//��� ��� ����
	if (block == NULL) {
		errorPrint("block is NULL");					//��������Ʈ
	}
	block->shape = shape;								//
}
static void blockSetAngle(Block* block, int angle) {	//��� ���� ����
	if (block == NULL) {
		errorPrint("block is NULL");					//��������Ʈ
	}
	block->angle = angle % BLOCK_ANGLE_NUM;				//������ ������?
}
static void blockSetColor(Block* block, Color color) {	//��� ���� ����
	if (block == NULL) {
		errorPrint("block is NULL");					//��������Ʈ
	}
	block->color = colors[color% BLOCK_COLOR_NUM];		//���� ������?.
}
static void blockSetLetter(Block* block, char* letter) {	//��� ���� ����
	strcpy(block->letter, letter);
}

// lotate controll
static void blockTurnRight(Block* block){					//����� ���������� 90�� ������ �Լ�
	block->angle = (block->angle + 1) % BLOCK_ANGLE_NUM;
}
static void blockTurnLeft(Block* block){					//����� �������� 90�� ������ �Լ�
	block->angle = (block->angle + (BLOCK_ANGLE_NUM-1)) % BLOCK_ANGLE_NUM;
}

// move controll	�Լ� ���� ������ ���� �Ҵ�
static void blockMoveTo(Block* block, int x, int y) {	//x, y���� ���ڷ� �޾� ���� ��ġ�� ����
	block->x = x;
	block->y = y;
}
static void blockMoveUp(Block* block) {					//�� ĭ ����
	block->y--;
}
static void blockMoveDown(Block* block) {				//�� ĭ �Ʒ���
	block->y++;
}
static void blockMoveRight(Block* block) {				//�� ĭ ����������
	block->x++;
}
static void blockMoveLeft(Block* block) {				//�� ĭ ��������
	block->x--;
}

static void blockDrawBlock(Block * block) {				//����� �׷��ִ� �Լ�
	GRAPHIC->setColor(block->color);					//�� �ٲٱ�
	GRAPHIC->setLetter(block->letter);				//���� �ٲٱ�
	
	BlockShape shape = blockGetShape(block);			//����� ���+���� ��ȯ
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (shape[y][x] == 1) {						//����� ������ŭ �ȴٰ� ���� 1�̸� drawPoint
				GRAPHIC->drawPoint(block->x + x, block->y + y);
			}
		}
	}
}
static void blockErase(Block* block) {					//����� ����� �Լ�
	GRAPHIC->setColor(EMPTY_COLOR);					//��� ������ ����
	GRAPHIC->setLetter((char*)EMPTY_LETTER);			//��� ���ڸ� ����
	BlockShape shape = blockGetShape(block);			//��� ���+���� ��ȯ
	int X = block->x;
	int Y = block->y;
	for (int y = Y; y < Y+BLOCK_HEIGHT; y++) {
		for (int x = X; x < X+BLOCK_WIDTH; x++) {
			if (shape[y-Y][x-X] == 1) {					//���� ����� ����(����4,����4)�� ������ ���� 1�̸� drawPoint
				GRAPHIC->drawPoint(x, y);
			}

		}
	}
}

static int blockRangeCheck(Block* block, int x, int y) {	//����� ������ üũ�ϴ� �Լ�
	int bx = block->x;
	int by = block->y;
	return (bx <= x && x < bx + BLOCK_WIDTH) && (by <= y && y < by + BLOCK_HEIGHT);
	//�����̸� 0, ���̸� 1�� ��ȯ
}