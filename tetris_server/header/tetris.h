#pragma once
#include "MainScreen.h"
#include "SubScreen.h"
#include "BlockCreator.h"
class Tetris {
private:
	int drawX, drawY;
	MainScreen* mainScreen;
	SubScreen* subScreen;
	BlockCreator* creator;
	bool endFlag;
	bool holdFlag = true;
	void press() {
		Block* next = subScreen->changeNext(creator->createBlock());	// 새 블록을 주고 등록되어 있던 next 블록을 얻어온다.
		mainScreen->press(next);
		holdFlag = true;
	}
public:
	Tetris(MainScreen* mainScreen, SubScreen* subScreen, BlockCreator* creator) : mainScreen(mainScreen), subScreen(subScreen), creator(creator){};
	void draw(int x, int y) {
		drawX = x;
		drawY = y;
		mainScreen->draw(drawX, drawY);
		subScreen->draw(drawX+mainScreen->getWidth()-mainScreen->getPointWidthSize(), drawY);
	}
	int moveDown() {	// 이동 성공여부 반환
		mainScreen->eraseBlock();
		bool succesFlag = mainScreen->moveDown();
		if (succesFlag) {
			mainScreen->eraseShadow();
			mainScreen->updateShadow();
			mainScreen->drawShadow();
			mainScreen->drawBlock();
		}
		else{
			press();
			if(mainScreen->clearLine()>0)
				mainScreen->erase();
			mainScreen->updateShadow();
			draw(drawX, drawY);
		}
		return succesFlag;
	}
	void moveRight() {
		mainScreen->eraseBlock();
		mainScreen->moveRight();
		mainScreen->eraseShadow();
		mainScreen->updateShadow();
		mainScreen->drawShadow();
		mainScreen->drawBlock();
	}
	void moveLeft() {
		mainScreen->eraseBlock();
		mainScreen->moveLeft();
		mainScreen->eraseShadow();
		mainScreen->updateShadow();
		mainScreen->drawShadow();
		mainScreen->drawBlock();
	}
	void turnRight() {
		mainScreen->eraseBlock();
		mainScreen->turnRight();
		mainScreen->eraseShadow();
		mainScreen->updateShadow();
		mainScreen->drawShadow();
		mainScreen->drawBlock();
	}
	void turnLeft() {
		mainScreen->eraseBlock();
		mainScreen->turnLeft();
		mainScreen->eraseShadow();
		mainScreen->updateShadow();
		mainScreen->drawShadow();
		mainScreen->drawBlock();
	}
	void dragDown() {
		while (moveDown()) Sleep(10);
	}
	void hold() {
		if (holdFlag) {
			mainScreen->eraseBlock();
			mainScreen->eraseShadow();
			Block* holdBlock = subScreen->changeHold(mainScreen->getBlock());
			if (holdBlock == NULL) {
				holdBlock = subScreen->changeNext(creator->createBlock());
			}
			mainScreen->setBlock(holdBlock);
			mainScreen->updateShadow();
			mainScreen->drawShadow();
			mainScreen->drawBlock();
			holdFlag = false;
		}
	}
	~Tetris() {
		delete mainScreen;
		delete subScreen;
	}
};