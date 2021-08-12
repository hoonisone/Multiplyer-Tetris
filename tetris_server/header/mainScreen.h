#pragma once

#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"

class MainScreen {
private:
	int w, h;
	Block* block;
	BlockBoard* board;
	BlockCreator* creator;
	ColorPainter* painter;// 테두리 그리기 용
public:
	MainScreen(BlockCreator* creator, BlockBoard* board, ColorPainter* painter) : creator(creator), board(board) , painter(painter){
		w = board->getWidhtNum()*board->getPointWidth() + 2*painter->getWidth();
		h = board->getHeightNum() * board->getPointHeight() + 2*painter->getHeight();
		block = creator->createBlock();
	}

	virtual void draw(int x, int y) {
		//rect()
		board->draw(x + 1, y + 1);
		block->draw(x + 1, y + 1);
	}
	virtual void erase() {

	}

	~MainScreen() {
		delete block;
		delete board;
		delete creator;
	}
};