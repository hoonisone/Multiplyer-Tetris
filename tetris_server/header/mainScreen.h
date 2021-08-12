#pragma once

#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "ColorPainter.h"

class MainScreen {
private:
	int drawX, drawY;	// 가장 최근에 그려진 위치
	int width, height;	// 가로 세로 길이(칸)
	Block* block;
	Block* shadow;
	BlockBoard* board;
	BlockCreator* creator;
	ColorPainter* painter;// 테두리 그리기 용
	virtual void moveHandler(BlockMove go, BlockMove back) {		// go를 수행한 뒤 범위가 안맞으면 다시 back수행
		block->erase(drawX + painter->getWidth(), drawY + painter->getHeight());
		block->move(go);	// 블록 move 함수
		if (board->rangeCheck(block)) {
			block->draw(drawX+painter->getWidth(), drawY+painter->getHeight());
		}
		else {
			block->move(back);// 블록 move 함수	go의 정 반대 수행
			block->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
		}
	}
	virtual void turnHandler(BlockTurn go, BlockTurn back) {	// go를 수행한 뒤 범위가 안맞으면 다시 back수행
		block->erase();
		block->turn(go);	// 블록 move 함수
		if (board->rangeCheck(block)) {
			block->draw(drawX, drawY);
		}
		else {
			block->turn(back);// 블록 move 함수	go의 정 반대 수행
			block->erase();
		}
	}
public:
	MainScreen(BlockCreator* creator, BlockBoard* board, ColorPainter* painter) : creator(creator), board(board), painter(painter) {
		width = board->getWidhtNum() * board->getPointWidth() / painter->getWidth() + 2;
		height = board->getHeightNum() * board->getPointHeight() / painter->getHeight() + 2;
		block = creator->createBlock();
	}
	virtual void draw(int x, int y) {
		drawX = x;
		drawY = y;
		painter->rectBorder(x, y, width, height);
		board->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
		block->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
	}
	virtual void erase(int x, int y) {
		ColorPainter({ " " }).rect(x, y, width, height);
	}
	virtual void moveUp() {	// 이동 -> 범위 체크 -> 재 조정
		moveHandler(BLOCK_MOVE_UP, BLOCK_MOVE_DOWN);
	}
	virtual void moveDown() {
		moveHandler(BLOCK_MOVE_DOWN, BLOCK_MOVE_UP);
	}
	virtual void moveRight() {
		moveHandler(BLOCK_MOVE_RIGHT, BLOCK_MOVE_LEFT);
	}
	virtual void moveLefe() {
		moveHandler(BLOCK_MOVE_LEFT, BLOCK_MOVE_RIGHT);
	}
	virtual void turnRight() {
		turnHandler(BLOCK_TURN_RIGHT, BLOCK_TURN_LEFT);
	}
	virtual void turnLeft() {
		turnHandler(BLOCK_TURN_LEFT, BLOCK_TURN_RIGHT);
	}

	~MainScreen() {
		delete block;
		delete board;
		delete creator;
	}
};