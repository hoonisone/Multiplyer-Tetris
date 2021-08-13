#pragma once

#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "ColorPainter.h"

class MainScreen {
private:
	int drawX, drawY;	// ���� �ֱٿ� �׷��� ��ġ
	int pointWidthNum, pointHeightNum;	// ���� ���� ����(ĭ)
	PointElement shadowPointElement = "��";
	Block* block = NULL;
	Block* shadow = NULL;
	BlockBoard* board = NULL;
	ColorPainter* painter;// �׵θ� �׸��� ��
	virtual bool moveHandler(BlockMove go, BlockMove back) {		// go�� ������ �� ������ �ȸ����� �ٽ� back����
		block->move(go);	// ��� move �Լ�
		if (!board->permitCheck(block)) {
			block->move(back);// ��� move �Լ�	go�� �� �ݴ� ����
			return false;
		}
		else {
			return true;
		}
	}
	virtual bool turnHandler(BlockTurn go, BlockTurn back) {	// go�� ������ �� ������ �ȸ����� �ٽ� back���� and ���� ���� ��ȯ
		block->turn(go);	// ��� move �Լ�
		if (!board->permitCheck(block)) {
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
	virtual void relocateShadow() {
		int originX = block->getX();
		int originY = block->getY();
		while (moveDown()); // �ٴ����� �������.
		shadow->moveTo(block->getX(), block->getY());	// �ٴ� ��ġ�� shadow ����
		block->moveTo(originX, originY);
	}
public:
	MainScreen(BlockBoard* board, Block *block, ColorPainter* painter) : board(board), block(block), painter(painter) {
		pointWidthNum = board->getWidhtNum() * board->getPointWidth() / painter->getWidth() + 2;
		pointHeightNum = board->getHeightNum() * board->getPointHeight() / painter->getHeight() + 2;
		updateShadow();
	}
	virtual void draw(int x, int y) {
		drawX = x;
		drawY = y;
		painter->rectBorder(x, y, pointWidthNum, pointHeightNum);
		board->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
		shadow->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
		block->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
	}
	virtual void erase(int x, int y) {
		ColorPainter* eraser = painter->getCopy();
		eraser->changeAllPointShapeElementInto(" ");
		eraser->rect(x, y, pointWidthNum, pointHeightNum);
		delete eraser;
	}
	virtual void erase() {
		erase(drawX, drawY);
	}
	virtual void eraseBlock() {
		block->erase();
	}
	virtual void drawBlock() {
		block->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
	}
	virtual void eraseShadow() {
		shadow->erase();
	}
	virtual void drawShadow(){
		shadow->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
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
	virtual void press(Block* block) {
		board->press(this->block);
		setBlock(block);
	}
	virtual void updateShadow() {	//�׸��� ����� ���� ����� ��ġ �ʱ�ȭ // ����� ��ü�Ǿ��� �� ȣ��ž� �Ѵ�.
		delete shadow;
		shadow = createShadow();
		relocateShadow();
	}
	virtual void setBlock(Block* block) {
		if (this->block != NULL) {
			delete this->block;
		}
		block->moveTo(pointWidthNum/2-BLOCK_WIDTH/2, 0);
		this->block = block;
		while (moveUp());
	}
	virtual Block* getBlock() {
		Block* block = this->block;
		this->block = NULL;
		return block;
	}
	int getWidth() {
		return pointWidthNum * painter->getWidth();
	}
	int getHeight() {
		return pointHeightNum * painter->getHeight();
	}
	int getPointWidthSize() {
		return painter->getWidth();
	}
	int getPointHeightSize() {
		return painter->getHeight();
	}
	int clearLine() {
		return board->clearLine();
	}
	~MainScreen() {
		delete block;
		delete shadow;
		delete board;
	}
};