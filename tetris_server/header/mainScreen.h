#pragma once

#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "ColorPainter.h"

class MainScreen {
private:
	int drawX, drawY;	// 가장 최근에 그려진 위치
	int pointWidthNum, pointHeightNum;	// 가로 세로 길이(칸)
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
	virtual void updateShadow() {	//그림자 블록을 새로 만들고 위치 초기화 // 블록이 교체되었을 때 호출돼야 한다.
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