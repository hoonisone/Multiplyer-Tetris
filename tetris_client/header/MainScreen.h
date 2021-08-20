#pragma once

#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "ColorPainter.h"

class MainScreen {
private:
	int drawX=0, drawY=0;	// 가장 최근에 그려진 위치
	int width, height;
	PointElement shadowPointElement = "□";
	Block* block = NULL;
	Block* shadow = NULL;
	BlockBoard* board = NULL;
	ColorPainter* painter;// 테두리 그리기 용
	virtual bool moveHandler(BlockMove go, BlockMove back) {		// go를 수행한 뒤 범위가 안맞으면 다시 back수행
		block->move(go);	// 블록 move 함수
		if (!board->permitCheck(block)) {
			block->move(back);// 블록 move 함수	go의 정 반대 수행
			return false;
		}
		else {
			return true;
		}
	}
	virtual bool turnHandler(BlockTurn go, BlockTurn back) {	// go를 수행한 뒤 범위가 안맞으면 다시 back수행 and 성공 여부 반환
		block->turn(go);	// 블록 move 함수
		if (!board->permitCheck(block)) {
			block->turn(back);// 블록 move 함수	go의 정 반대 수행
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
		while (moveDown()); // 바닥으로 끓어내린다.
		shadow->moveTo(block->getX(), block->getY());	// 바닥 위치에 shadow 세팅
		block->moveTo(originX, originY);
	}
	virtual void dragUp() {
		while (moveUp());
	}
public:
	MainScreen(BlockBoard* board, Block *block, ColorPainter* painter) : board(board), painter(painter) {
		width = board->getWidth() + painter->getWidth() * 2;
		height = board->getHeight() + painter->getHeight() * 2;
		setBlock(block);
		updateShadow();
	}
	virtual bool moveUp() {	// 이동 -> 범위 체크 -> 재 조정
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
	virtual bool checkPermit() {
		return board->permitCheck(block);
	}
	virtual void updateShadow() {	//그림자 블록을 새로 만들고 위치 초기화 // 블록이 교체되었을 때 호출돼야 한다.
		delete shadow;
		shadow = createShadow();
		relocateShadow();
	}
	virtual void setBlock(Block* block) {
		if (this->block != NULL) {
			delete this->block;
		}
		block->moveTo(board->getPointWidhtNum()/2-BLOCK_WIDTH/2, 0);
		this->block = block;
		dragUp();
	}

	virtual Block* getBlock() {
		Block* block = this->block;
		this->block = NULL;
		return block;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
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

	virtual void drawPointSetting(int drawX, int drawY) {
		this->drawX = drawX;
		this->drawY = drawY;
	}
	virtual void draw(int drawX, int drawY) {
		drawPointSetting(drawX, drawY);
		redrawFrame();
		redrawBoard();
		redrawShadow();
		redrawBlock();
	}
	virtual void redrawFrame() {
		painter->rectBorder(drawX, drawY, width, height, CURSOR_STD);
	}
	virtual void redrawBoard() {
		board->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
	}
	virtual void redrawShadow() {
		shadow->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
	}
	virtual void redrawBlock() {
		block->draw(drawX + painter->getWidth(), drawY + painter->getHeight());
	}
	virtual void erase() {
		ColorPainter* eraser = painter->getCopy();
		eraser->changeAllPointShapeElementInto(" ");
		eraser->rect(drawX, drawY, width, height);
		delete eraser;
	}
	virtual void eraseBlock() {
		block->erase();
	}
	virtual void eraseShadow() {
		shadow->erase();
	}
	virtual void eraseBoard() {
		board->erase();
	}

	~MainScreen() {
		delete block;
		delete shadow;
		delete board;
	}
};