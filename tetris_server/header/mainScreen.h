#pragma once

#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "ColorPainter.h"

class MainScreen {
private:
	int width, height;	// 가로 세로 길이(칸)
	Block* block;
	BlockBoard* board;
	BlockCreator* creator;
	ColorPainter* painter;// 테두리 그리기 용
public:
	MainScreen(BlockCreator* creator, BlockBoard* board, ColorPainter* painter) : creator(creator), board(board) , painter(painter){
		width = board->getWidhtNum()*board->getPointWidth()/painter->getWidth() + 2;
		height = board->getHeightNum() * board->getPointHeight()/painter->getHeight() + 2;
		block = creator->createBlock();
	}

	virtual void draw(int x, int y) {
		painter->rectBorder(x, y, width, height);
		board->draw(x + painter->getWidth(), y + painter->getHeight());
		block->draw(x + painter->getWidth(), y + painter->getHeight());
	}
	virtual void erase(int x, int y) {
		ColorPainter({ " " }).rect(x, y, width, height);
	}

	~MainScreen() {
		delete block;
		delete board;
		delete creator;
	}
};