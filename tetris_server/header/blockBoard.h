//#pragma once
//#include "graphic.h"
//#include "block.h"
//
//#define BOARD_WIDTH 10
//#define BOARD_HEIGHT 20
//#define LETTER_SIZE
//
//#define BLOCK_BOARD blockBoardFunctionCreate()
//
//typedef Color** BlockBoardData;
//
//typedef struct BlockBoard {
//	int x, y;
//	int width, height;
//	BlockBoardData data;
//	Letter letter;
//};
//
//typedef struct BlockBoardFunction {
//	BlockBoard* (*create)(int x, int y, int width, int height);
//	void (*moveTo)(BlockBoard* blockBoard, int x, int y);
//	void (*pressBlock)(BlockBoard* blockBoard, Block* block);
//	void (*changeSize)(BlockBoard* blockBoard, int newWidth, int newHeight);
//	int (*blockPositionPermitCheck)(BlockBoard* blockBoard, Block* block);
//	void (*del)(BlockBoard* blockBoard);
//};
//
//BlockBoardFunction* blockBoardFunctionCreate();
