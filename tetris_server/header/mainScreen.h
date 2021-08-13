#pragma once

#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "ColorPainter.h"

class MainScreen {
public:
	int drawX, drawY;	// ���� �ֱٿ� �׷��� ��ġ
	int width, height;	// ���� ���� ����(ĭ)
	PointElement shadowPointElement = "��";
	Block* block = NULL;
	Block* shadow = NULL;
	BlockBoard* board = NULL;
	ColorPainter* painter;// �׵θ� �׸��� ��
	virtual bool moveHandler(BlockMove go, BlockMove back) {		// go�� ������ �� ������ �ȸ����� �ٽ� back����
		block->move(go);	// ��� move �Լ�
		if (!board->rangeCheck(block)) {
			block->move(back);// ��� move �Լ�	go�� �� �ݴ� ����
			return false;
		}
		else {
			return true;
		}
	}
	virtual bool turnHandler(BlockTurn go, BlockTurn back) {	// go�� ������ �� ������ �ȸ����� �ٽ� back���� and ���� ���� ��ȯ
		block->turn(go);	// ��� move �Լ�
		if (!board->rangeCheck(block)) {
			block->turn(back);// ��� move �Լ�	go�� �� �ݴ� ����
			return false;
		}
		else {
			return true;
		}
	}
	virtual Block* createShadow() const {
		Block* shadow = this->block->getCopy();
		ColorPainter* painter = shadow->getPainter()->getCopy();
		painter->changeAllPointShapeElementInto(shadowPointElement);
		shadow->setPainter(painter);
		return shadow;
	}
public:
	MainScreen(BlockBoard* board, Block *block, ColorPainter* painter) : board(board), block(block), painter(painter) {
		width = board->getWidhtNum() * board->getPointWidth() / painter->getWidth() + 2;
		height = board->getHeightNum() * board->getPointHeight() / painter->getHeight() + 2;
		initShadow();
	}
	virtual void draw(int x, int y) {
		drawX = x;
		drawY = y;
		painter->rectBorder(x, y, width, height);
		board->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
		block->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
		shadow->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
	}
	virtual void erase(int x, int y) {
		ColorPainter({ " " }).rect(x, y, width, height);
	}
	virtual void eraseBlock() {
		block->erase();
	}
	virtual void drawBlock() {
		block->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
	}
	virtual bool moveUp() {	// �̵� -> ���� üũ -> �� ����
		return moveHandler(BLOCK_MOVE_UP, BLOCK_MOVE_DOWN);
	}
	virtual bool moveDown() {
		return moveHandler(BLOCK_MOVE_DOWN, BLOCK_MOVE_UP);
	}
	virtual bool moveRight() {
		return moveHandler(BLOCK_MOVE_RIGHT, BLOCK_MOVE_LEFT);
	}
	virtual bool moveLeft() {
		return moveHandler(BLOCK_MOVE_LEFT, BLOCK_MOVE_RIGHT);
	}
	virtual bool turnRight() {
		return turnHandler(BLOCK_TURN_RIGHT, BLOCK_TURN_LEFT);
	}
	virtual bool turnLeft() {
		return turnHandler(BLOCK_TURN_LEFT, BLOCK_TURN_RIGHT);
	}
	virtual void press() {
		board->press(block);
	}
	virtual void initShadow() {	//�׸��� ����� ���� ����� ��ġ �ʱ�ȭ // ����� ��ü�Ǿ��� �� ȣ��ž� �Ѵ�.
		delete shadow;
		shadow = createShadow();
		updateShadow();
	}
	virtual void updateShadow() { // shadow position ����
		int originX = block->getX();
		int originY = block->getY();
		while (moveDown()); // �ٴ����� �������.
		shadow->moveTo(block->getX(), block->getY());	// �ٴ� ��ġ�� shadow ����
		block->moveTo(originX, originY);
	}
	~MainScreen() {
		delete block;
		delete shadow;
		delete board;
	}
};