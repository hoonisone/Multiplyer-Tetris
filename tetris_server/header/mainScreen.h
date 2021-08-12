#pragma once

#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "ColorPainter.h"

class MainScreen {
private:
	int drawX, drawY;	// ���� �ֱٿ� �׷��� ��ġ
	int width, height;	// ���� ���� ����(ĭ)
	Block* block;
	Block* shadow;
	BlockBoard* board;
	BlockCreator* creator;
	ColorPainter* painter;// �׵θ� �׸��� ��
	virtual void moveHandler(BlockMove go, BlockMove back) {		// go�� ������ �� ������ �ȸ����� �ٽ� back����
		block->erase(drawX + painter->getWidth(), drawY + painter->getHeight());
		block->move(go);	// ��� move �Լ�
		if (board->rangeCheck(block)) {
			block->draw(drawX+painter->getWidth(), drawY+painter->getHeight());
		}
		else {
			block->move(back);// ��� move �Լ�	go�� �� �ݴ� ����
			block->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
		}
	}
	virtual void turnHandler(BlockTurn go, BlockTurn back) {	// go�� ������ �� ������ �ȸ����� �ٽ� back����
		block->erase();
		block->turn(go);	// ��� move �Լ�
		if (board->rangeCheck(block)) {
			block->draw(drawX, drawY);
		}
		else {
			block->turn(back);// ��� move �Լ�	go�� �� �ݴ� ����
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
	virtual void moveUp() {	// �̵� -> ���� üũ -> �� ����
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