#include <stdio.h>
#include <windows.h>
#include "block.h"
#include "graphic.h"
#include "error.h"
#include "random.h"

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

// 블록 7가지 모양 값
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
// 7가지 색을 배열에 저장
static int colors[BLOCK_COLOR_NUM] = { LIGHT_BLUE, LIGHT_GREEN, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, BRIGHT_WHITE, LIGHT_AQUA };

// block function object
BlockFunction* getBlockFunction() {// return singleton block function object
   static BlockFunction* blockFunction = createBlockFunction(); // createBlockFunction 함수를 이용해 blockFunction 생성
   return blockFunction; // 생성된 blockFunction의 주소값 반환
}
static BlockFunction* createBlockFunction() {// block function object constructor
   BlockFunction* bf = (BlockFunction*)malloc(sizeof(BlockFunction)); // BlockFunction 크기만큼 동적할당
   bf->create = blockCreate;
   bf->createRandomBlock = blockCreateRandomBlock;
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
   bf->draw = blockDrawBlock;
   bf->erase = blockErase;

   bf->rangeCheck = blockRangeCheck;
   return bf;
}

// internal method of block object
static Block* blockCreate(int x, int y, int color, int shape, int angle)   // block constructor
{
   Block* object = (Block*)malloc(sizeof(Block)); // Block 크기만큼 동적할당
   object->x = x; // x좌표 저장
   object->y = y; // y좌표 저장
   blockSetColor(object, color); // 블록의 색 저장
   object->shape = shape%BLOCK_SHAPE_NUM; // 블록의 모양이 BLOCK_SHAPE_NUM마다 반복
   object->angle = angle%BLOCK_ANGLE_NUM; // 블록의 색이 BLOCK_ANGLE_NUM마다 반복
   strcpy(object->letter, BLOCK_DEFAULT_LETTER); // BLOCK_DEFAULT_LETTER 모양으로 블록 구성
   return object; // 블록의 주소값 반환
}
static Block* blockCreateRandomBlock() {
   int shape = RANDOM->getValue() % BLOCK_SHAPE_NUM; // 랜덤 값 생성 후 블록 모양 개수로 나눈 나머지 저장
   int angle = RANDOM->getValue() % BLOCK_ANGLE_NUM; // 랜덤 값 생성 후 블록 각도 개수로 나눈 나머지 저장
   Color color = RANDOM->getValue() % BLOCK_COLOR_NUM; // 랜덤 값 생성 후 블록 색 개수로 나눈 나머지 저장
   return BLOCK->create(0, 0, color, shape, angle); // 블록 생성 후 주소값 반환
}
static Block* blockCopy(Block* block) {
   Block* copyBlock = blockCreate(0, 0, 0, 0, 0); // 블록 생성
   memcpy(copyBlock, block, sizeof(Block)); // 생성한 블록에 block의 메모리 복사
   return copyBlock; // 복사 받은 copyBlock의 주소값 반환
}

// getter setter
static BlockShape blockGetShape(Block* block) 
{
   return BLOCK_SHAPE[block->shape][block->angle]; // 블록의 모양, 각도에 맞는 값 반환
}
static void blockSetShape(Block* block, int shape) {
   if (block == NULL) {
      errorPrint("block is NULL"); // 블록 값이 NULL인 경우 에러 출력
   }
   block->shape = shape; // 블록의 모양을 shape로 바꿈
}
static void blockSetAngle(Block* block, int angle) {
   if (block == NULL) {
      errorPrint("block is NULL"); // 블록 값이 NULL인 경우 에러 출력
   }
   block->angle = angle % BLOCK_ANGLE_NUM; // 블록의 각도를 angle을 각도의 개수로 나눈 나머지로 바꿈
}
static void blockSetColor(Block* block, Color color) {
   if (block == NULL) {
      errorPrint("block is NULL"); // 블록 값이 NULL인 경우 에러 출력
   }
   block->color = colors[color% BLOCK_COLOR_NUM]; // 블록의 색을 color를 colors배열의 색의 개수로 나눈 나머지번째의 값으로 바꿈
}
static void blockSetLetter(Block* block, char* letter) {
   strcpy(block->letter, letter); // letter모양을 저장
}
`
// lotate controll
static void blockTurnRight(Block* block){
   block->angle = (block->angle + 1) % BLOCK_ANGLE_NUM; // 블록을 돌려 오른쪽으로 회전된 모양으로 바꿈
}
static void blockTurnLeft(Block* block){
   block->angle = (block->angle + (BLOCK_ANGLE_NUM-1)) % BLOCK_ANGLE_NUM; // 블록을 돌려 왼쪽으로 회전된 모양으로 바꿈
}

// move controll
static void blockMoveTo(Block* block, int x, int y) {
   block->x = x; // 블록의 x좌표를 x로 변경
   block->y = y; // 블록의 y좌표를 y로 변경
}
static void blockMoveUp(Block* block) {
   block->y--; // 블록의 y좌표 1감소
}
static void blockMoveDown(Block* block) {
   block->y++; // 블록의 y좌표 1증가
}
static void blockMoveRight(Block* block) {
   block->x++; // 블록의 x좌표 1증가
}
static void blockMoveLeft(Block* block) {
   block->x--; // 블록의 x좌표 1감소
}

static void blockDrawBlock(Block * block) {
   GRAPHIC->changeColor(block->color); // 블록의 색 설정
   GRAPHIC->changeLetter(block->letter); // 블록을 구성하는 글자 설정
   
   BlockShape shape = blockGetShape(block); // 블록의 모양, 각도 저장
   for (int y = 0; y < BLOCK_HEIGHT; y++) {
      for (int x = 0; x < BLOCK_WIDTH; x++) {
         if (shape[y][x] == 1) { // 블록의 크기만큼 반복하며 1이 저장된 칸에
            GRAPHIC->drawPoint(block->x + x, block->y + y); // 블록 그리기
         }
      }
   }
}
static void blockErase(Block* block) {
   GRAPHIC->changeColor(EMPTY_COLOR); // 색에 저장된 값 지우기
   GRAPHIC->changeLetter((char*)EMPTY_LETTER); // 블록을 구성하는 글자 지우기
   BlockShape shape = blockGetShape(block); // 블록의 모양, 각도 저장
   int X = block->x; // 블록의 x좌표 저장
   int Y = block->y; // 블록의 y좌표 저장
   for (int y = Y; y < Y+BLOCK_HEIGHT; y++) {
      for (int x = X; x < X+BLOCK_WIDTH; x++) {
         if (shape[y-Y][x-X] == 1) { // 블록의 크기만큼 반복하며 1이 저장된 칸에
            GRAPHIC->drawPoint(x, y); // 블록 지우기
         }

      }
   }
}

static int blockRangeCheck(Block* block, int x, int y) {
   int bx = block->x; // 블록의 x좌표 저장
   int by = block->y; // 블록의 y좌표 저장
   return (bx <= x && x < bx + BLOCK_WIDTH) && (by <= y && y < by + BLOCK_HEIGHT); // 블록의 너비, 높이범위 안에서 블록의 범위 반환
}