#include "blockBoard.h"
#include "error.h"
#include "block.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static BlockBoard* blockBoardCreate(int x, int y);
static BlockBoardFunction* blockBoardFunctionCreate();
static void blockBoardMoveTo(BlockBoard* blockBoard, int x, int y);
static Color** blockBoardCreateNewBoard(int width, int height);
static void blockBoardChangeSize(BlockBoard* blockBoard, int newWidth, int newHeight);
static void blockBoardDraw(BlockBoard* blockBoard);
static void blockBoardErase(BlockBoard* blockBoard);
static void blockBoardPressBlock(BlockBoard* blockBoard, Block* block);
static int blockBoardIsPointInRange(BlockBoard* blockBoard, int x, int y);
static int screenCurBlockPositionPermitCheck(BlockBoard* blockBoard, Block* block);
static int blockBoardIsBlockOutOfRange(BlockBoard* blockBoard, Block* block);
static int blockBoardBlockCrashCheck(BlockBoard* blockBoard, Block* block);
static void blockBoardDelete(BlockBoard* blockBoard);
static void blockBoardDeleteData(BlockBoard* blockBoard);


static BlockBoard* blockBoardCreate(int x, int y) {
	BlockBoard* object = (BlockBoard*)malloc(sizeof(BlockBoard));
	blockBoardChangeSize(object, BOARD_WIDTH, BOARD_HEIGHT);
	blockBoardMoveTo(object, x, y);
	return object;
}
static BlockBoardFunction* blockBoardFunctionCreate() {
	BlockBoardFunction* object = (BlockBoardFunction*)malloc(sizeof(BlockBoardFunction));
	object->create = blockBoardCreate;
	object->moveTo = blockBoardMoveTo;
	object->pressBlock = blockBoardPressBlock;
	object->changeSize = blockBoardChangeSize;
	object->blockPositionPermitCheck = screenCurBlockPositionPermitCheck;
	object->del = blockBoardDelete;
	return object;
}
static BlockBoardFunction* getBlockBoardFunction() {
	static BlockBoardFunction* blockBoardFunction = blockBoardFunctionCreate();
	return blockBoardFunction;
}
static void blockBoardMoveTo(BlockBoard* blockBoard, int x, int y) {
	if (blockBoard == NULL) {
		errorPrint("blockBoard is NULL");
	}
	blockBoardErase(blockBoard);	// erase before moving
	blockBoard->x = x;
	blockBoard->y = y;
	blockBoardDraw(blockBoard);		// draw agrin after moving
}
static Color** blockBoardCreateNewBoard(int width, int height) {
	Color** newBoard = (Color**)malloc(sizeof(Color*) * height);
	for (int y = 0; y < height; y++) {
		newBoard[y] = (int*)calloc(width, sizeof(int));
	}
	return newBoard;
}
static void blockBoardChangeSize(BlockBoard* blockBoard, int newWidth, int newHeight) {
	if (blockBoard == NULL) {
		errorPrint("blockBoard is NULL");
	}
	Color** oldBoard = blockBoard->data;
	Color** newBoard = blockBoardCreateNewBoard(newWidth, newHeight);

	if (oldBoard == NULL) {	// when to be called first
		blockBoard->data = newBoard;
	}
	else {
		// erase origin board
		blockBoardErase(blockBoard); 
		
		// compute common area
		int oldWidth = blockBoard->width;
		int oldHeight = blockBoard->height;
		int minWidth = (newWidth < oldWidth) ? newWidth : oldWidth;
		int minHeight = (newHeight < oldHeight) ? newHeight : oldHeight;

		// copy data in origin board into new board
		for (int y = 0; y < minHeight; y++) {	
			memcpy(newBoard[newHeight - 1 - y], oldBoard[oldHeight - 1 - y], minWidth);
		}

		// delete origin board
		for (int i = 0; i < oldHeight; i++) {	
			free(oldBoard[i]);
		}
		free(oldBoard);
	}

	blockBoard->data= newBoard;
	blockBoard->width = newWidth;
	blockBoard->height = newHeight;
	blockBoardDraw(blockBoard);
}
static void blockBoardDraw(BlockBoard* blockBoard) {
	if (blockBoard->data == NULL) {
		errorPrint("blockBoard's data is NULL");
	}
	int X = blockBoard->x;
	int Y = blockBoard->y;
	int W = blockBoard->width;
	int H = blockBoard->height;
	for (int y = Y; y < Y+W; y++) {
		for (int x = X; x < X+W; x++) {
			Color color = blockBoard->data[y][x];
			if (color != 0) {
				GRAPHIC->changeLetter(blockBoard->letter);
				GRAPHIC->changeColor(color);
				GRAPHIC->drawPoint(x, y);
			}
		}
	}
}
static void blockBoardErase(BlockBoard* blockBoard) {
	if (blockBoard->data == NULL) {
		errorPrint("blockBoard's data is NULL");
	}
	int X = blockBoard->x;
	int Y = blockBoard->y;
	int W = blockBoard->width;
	int H = blockBoard->height;
	GRAPHIC->changeLetter(EMPTY_LETTER);
	GRAPHIC->changeColor(EMPTY_COLOR);
	for (int y = Y; y < Y + W; y++) {
		for (int x = X; x < X + W; x++) {
			Color color = blockBoard->data[y][x];
			if (color != 0) {
				GRAPHIC->drawPoint(x, y);
			}
		}
	}
}
static void blockBoardPressBlock(BlockBoard* blockBoard, Block* block) {
	if (blockBoard == NULL) {
		errorPrint("blockBoard is NULL");
	}
	BlockBoardData data = blockBoard->data;
	if (data == NULL) {
		errorPrint("blockBoard's data is NULL");
	}
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	int color = block->color;
	BlockShape shape = BLOCK->getShape(block);

	int X = block->x;
	int Y = block->y;
	for (int y = Y; y < Y+BLOCK_HEIGHT; y++) {
		for (int x = X; x < X+BLOCK_HEIGHT; x++) {
			if(blockBoardIsPointInRange(blockBoard, x, y)){
				if (shape[y-Y][x-X] == 1) {
					data[y-blockBoard->y][x - blockBoard->y] = color;
				}
			}
		}
	}
}
static int blockBoardIsPointInRange(BlockBoard* blockBoard, int x, int y) {
	int X = blockBoard->x;
	int Y = blockBoard->y;
	int W = blockBoard->width;
	int H= blockBoard->height;
	if (X <= x && x < X+W)
		if (Y <= y && y < Y+H)
			return 1;
	return 0;
}
static int screenCurBlockPositionPermitCheck(BlockBoard* blockBoard, Block * block) {
	if (blockBoard == NULL) {
		errorPrint("blockBoard is NULL");
	}
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	if (blockBoardIsBlockOutOfRange(blockBoard, block))
		return 0;
	if (blockBoardBlockCrashCheck(blockBoard, block))
		return 0;
	return 1;
}
static int blockBoardIsBlockOutOfRange(BlockBoard* blockBoard, Block* block) {
	if (blockBoard == NULL) {
		errorPrint("blockBoard is NULL");
	}
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	int X = block->x;
	int Y = block->y;
	BlockShape shape = BLOCK->getShape(block);
	for (int y = Y; y < Y + BLOCK_HEIGHT; y++) {
		for (int x = X; x < X + BLOCK_WIDTH; x++) {
			if (shape[y][x] == 1 && !blockBoardIsPointInRange(blockBoard, x, y))
				return 1;
		}
	}
	return 0;
}
static int blockBoardBlockCrashCheck(BlockBoard* blockBoard, Block* block) {
	if (blockBoard == NULL) {
		errorPrint("blockBoard is NULL");
	}
	if (block == NULL) {
		errorPrint("block is NULL");
	}
	int blockX = block->x;
	int blockY = block->y;
	int boardX = blockBoard->x;
	int boardY = blockBoard->y;
	BlockShape shape = BLOCK->getShape(block);
	BlockBoardData data = blockBoard->data;
	for (int y = blockY; y < blockY + BLOCK_HEIGHT; y++) {
		for (int x = blockX; x < blockX + BLOCK_WIDTH; x++) {
			if (shape[y - blockY][x - blockX] == 1 &&
				blockBoardIsPointInRange(blockBoard, x, y)&&
				data[y-boardY][x- boardX] != 0) {
				return 1;
			}
		}
	}
	return 0;
}
static void blockBoardDelete(BlockBoard* blockBoard) {
	if (blockBoard->data == NULL) {
		errorPrint("blockBoard's data is NULL");
	}
	blockBoardDeleteData(blockBoard);
	free(blockBoard);
}
static void blockBoardDeleteData(BlockBoard* blockBoard) {
	for (int y = 0; y < blockBoard->height; y++){
		free(blockBoard->data[y]);
	}
	free(blockBoard->data);
}
