#include <stdio.h>
#include <windows.h>
#include "block.h"		//블록 구조체 정의, 테트리스 블록 모양 정의, 블록 문자 유니코드 정의
#include "graphic.h"	//블록 그래픽 관련 헤더파일
#include "error.h"		//에러 관련 헤더파일
#include "random.h"		//랜덤 헤더파일

//함수 선언 부분
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

static Color BLOCK_SHAPE[7][4][4][4] = {// 블록 데이터, [7모양][4각도][세로크기][가로크기]
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
//색 값들을 저장하는 int형 colors배열 생성 각 색들은 graphic.h에서 정수형으로 정의되어있음
// block function object	블록 함수 객체
BlockFunction* getBlockFunction() {// return singleton block function object	싱글턴 블록 함수 객체 반환
	static BlockFunction* blockFunction = createBlockFunction();
	return blockFunction;
}

static BlockFunction* createBlockFunction() {// block function object constructor	블록 함수 객체 생성자
	BlockFunction* bf = (BlockFunction*)malloc(sizeof(BlockFunction));	//bf동적할당
	//구조체 멤버들을 각 함수들에 할당
	bf->create = blockCreate;							//블록의 x,y좌표, 모양, 각도, 색깔을 받음
	bf->createRandomBlock = blockCreateRandomBlock;		//블록의 모양, 각도, 색깔을 랜덤으로 할당시킴
	bf->copy = blockCopy;								//블록의 데이터를 복사함

	// get set
	bf->getShape = blockGetShape;
	bf->setShape = blockSetShape;
	bf->setAngle = blockSetAngle;
	bf->setColor = blockSetColor;
	bf->setLetter = blockSetLetter;

	// contoll
	bf->turnRight = blockTurnRight;						//블록을 오른쪽으로 90도 회전
	bf->turnLeft = blockTurnLeft;						//블록을 왼쪽으로 90도 회전
	bf->moveTo = blockMoveTo;							//블록을 좌측상단 기준 인자로 받은 x,y좌표로 옮김
	bf->moveUp = blockMoveUp;							//블록을 한 칸 위로
	bf->moveDown = blockMoveDown;						//블록을 한 칸 아래로
	bf->moveRight = blockMoveRight;						//블록을 한 칸 오른쪽으로
	bf->moveLeft = blockMoveLeft;						//블록을 한 칸 왼쪽으로
	// draw
	bf->draw = blockDrawBlock;							//할당된 값으로 블록을 그림
	bf->erase = blockErase;								//블록을 지움

	bf->rangeCheck = blockRangeCheck;					//블록의 범위를 체크함
	return bf;											//bf반환
}

// internal method of block object	블록 객체의 내부 메소드
static Block* blockCreate(int x, int y, int color, int shape, int angle)	// block constructor	블록 생성자
{
	Block* object = (Block*)malloc(sizeof(Block));	//object동적할당
	object->x = x;									//블록 좌측상단의 x좌표
	object->y = y;									//블록 좌측상단의 y좌표
	blockSetColor(object, color);					//
	object->shape = shape%BLOCK_SHAPE_NUM;			//블록 모양
	object->angle = angle%BLOCK_ANGLE_NUM;			//블록 각도
	strcpy(object->letter, BLOCK_DEFAULT_LETTER);	//블록 문자열(유니코드+널문자) 복사
	return object;									//object반환
}
static Block* blockCreateRandomBlock() {				//랜덤 헤더파일 참조, 블럭의 모양, 각도, 색깔을 랜덤으로 할당시켜 반환
	int shape = RANDOM->getValue() % BLOCK_SHAPE_NUM;	//블록 모양 랜덤 할당
	int angle = RANDOM->getValue() % BLOCK_ANGLE_NUM;	//블록 각도 랜덤 할당
	Color color = RANDOM->getValue() % BLOCK_COLOR_NUM;	//블록 색깔 랜덤 할당
	return BLOCK->create(0, 0, color, shape, angle);	//모양, 각도, 색깔값이 할당된 블록 반환
}
static Block* blockCopy(Block* block) {				//블럭을 복사함
	Block* copyBlock = blockCreate(0, 0, 0, 0, 0);	//copyBlock변수 선언
	memcpy(copyBlock, block, sizeof(Block));		//copyBlock변수에 받은 인자값들을 memcpy메모리복사 
	return copyBlock;								//copyBlock 반환
}

// getter setter
static BlockShape blockGetShape(Block* block)		//블록 모양+각도 함수
{
	return BLOCK_SHAPE[block->shape][block->angle];	//블록 모양, 각도 반환
}
static void blockSetShape(Block* block, int shape) {	//블록 모양 설정
	if (block == NULL) {
		errorPrint("block is NULL");					//에러프린트
	}
	block->shape = shape;								//
}
static void blockSetAngle(Block* block, int angle) {	//블록 각도 설정
	if (block == NULL) {
		errorPrint("block is NULL");					//에러프린트
	}
	block->angle = angle % BLOCK_ANGLE_NUM;				//각도값 재정비?
}
static void blockSetColor(Block* block, Color color) {	//블록 색깔 설정
	if (block == NULL) {
		errorPrint("block is NULL");					//에러프린트
	}
	block->color = colors[color% BLOCK_COLOR_NUM];		//색값 재정비?.
}
static void blockSetLetter(Block* block, char* letter) {	//블록 문자 설정
	strcpy(block->letter, letter);
}

// lotate controll
static void blockTurnRight(Block* block){					//블록을 오른쪽으로 90도 돌리는 함수
	block->angle = (block->angle + 1) % BLOCK_ANGLE_NUM;
}
static void blockTurnLeft(Block* block){					//블록을 왼쪽으로 90도 돌리는 함수
	block->angle = (block->angle + (BLOCK_ANGLE_NUM-1)) % BLOCK_ANGLE_NUM;
}

// move controll	함수 내부 변수로 값을 할당
static void blockMoveTo(Block* block, int x, int y) {	//x, y값을 인자로 받아 현재 위치로 변경
	block->x = x;
	block->y = y;
}
static void blockMoveUp(Block* block) {					//한 칸 위로
	block->y--;
}
static void blockMoveDown(Block* block) {				//한 칸 아래로
	block->y++;
}
static void blockMoveRight(Block* block) {				//한 칸 오른쪽으로
	block->x++;
}
static void blockMoveLeft(Block* block) {				//한 칸 왼쪽으로
	block->x--;
}

static void blockDrawBlock(Block * block) {				//블록을 그려주는 함수
	GRAPHIC->setColor(block->color);					//색 바꾸기
	GRAPHIC->setLetter(block->letter);				//문자 바꾸기
	
	BlockShape shape = blockGetShape(block);			//블록의 모양+각도 반환
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (shape[y][x] == 1) {						//블록의 범위만큼 훑다가 값이 1이면 drawPoint
				GRAPHIC->drawPoint(block->x + x, block->y + y);
			}
		}
	}
}
static void blockErase(Block* block) {					//블록을 지우는 함수
	GRAPHIC->setColor(EMPTY_COLOR);					//블록 색깔을 없앰
	GRAPHIC->setLetter((char*)EMPTY_LETTER);			//블록 문자를 없앰
	BlockShape shape = blockGetShape(block);			//블록 모양+각도 반환
	int X = block->x;
	int Y = block->y;
	for (int y = Y; y < Y+BLOCK_HEIGHT; y++) {
		for (int x = X; x < X+BLOCK_WIDTH; x++) {
			if (shape[y-Y][x-X] == 1) {					//현재 블록의 범위(가로4,세로4)를 훑으며 값이 1이면 drawPoint
				GRAPHIC->drawPoint(x, y);
			}

		}
	}
}

static int blockRangeCheck(Block* block, int x, int y) {	//블록의 범위를 체크하는 함수
	int bx = block->x;
	int by = block->y;
	return (bx <= x && x < bx + BLOCK_WIDTH) && (by <= y && y < by + BLOCK_HEIGHT);
	//거짓이면 0, 참이면 1을 반환
}