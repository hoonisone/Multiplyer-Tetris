#pragma once
#include "MainScreen.h"
#include "SubScreen.h"
#include "BlockCreator.h"
#include "scoreManager.h"

class Tetris {
private:
	int drawX, drawY;
	MainScreen* mainScreen;
	SubScreen* subScreen;
	BlockCreator* creator;
	ScoreManager* scoreManager;
	bool endFlag;
	bool holdFlag = true;
	void press() {
		Block* next = subScreen->changeNext(creator->createBlock());	// �� ����� �ְ� ��ϵǾ� �ִ� next ����� ���´�.
		mainScreen->press(next);
		holdFlag = true;
	}
public:
	Tetris(MainScreen* mainScreen, SubScreen* subScreen, BlockCreator* creator, ScoreManager * scoreManager) : mainScreen(mainScreen), subScreen(subScreen), creator(creator), scoreManager(scoreManager){
	};
	void draw(int x, int y) {
		drawX = x;
		drawY = y;
		drawScoreBoard();
		drawMainScreen();
		drawSubScreen();
	}
	virtual void drawMainScreen() {
		mainScreen->draw(drawX, drawY);
	}
	virtual void drawSubScreen() {
		subScreen->draw(drawX + mainScreen->getWidth() - mainScreen->getPointWidthSize(), drawY);
	}
	virtual void drawScoreBoard(){
		scoreManager->draw(drawX, drawY + mainScreen->getHeight() - 1);
	}
	int moveDown() {	// �̵� �������� ��ȯ
		mainScreen->eraseBlock();
		mainScreen->eraseShadow();
		bool succesFlag = mainScreen->moveDown();
		if (!succesFlag){	// �ٴڿ� ��Ҵٸ�
			press();
			scoreManager->addBlock(1);	// ���� �߰�(��� �� ��)
			int lineClearNum = mainScreen->clearLine();	// �ϼ��� ���� ����� & ������ ���� ��ȯ
			if(lineClearNum>0){
				scoreManager->addLine(lineClearNum);	// ���� �߰�(���� n��)
			};
			scoreManager->redrawContent();
			mainScreen->eraseBoard();
		}
		mainScreen->updateShadow();
		mainScreen->redrawBoard();	// ���� �ٽ� �׸���
		mainScreen->redrawShadow();
		mainScreen->redrawBlock();
		return succesFlag;
	}
	void moveRight() {
		mainScreen->eraseBlock();
		mainScreen->eraseShadow();
		mainScreen->moveRight();
		mainScreen->updateShadow();
		mainScreen->redrawShadow();
		mainScreen->redrawBlock();
	}
	void moveLeft() {
		mainScreen->eraseBlock();
		mainScreen->eraseShadow();
		mainScreen->moveLeft();
		mainScreen->updateShadow();
		mainScreen->redrawShadow();
		mainScreen->redrawBlock();
	}
	void turnRight() {
		mainScreen->eraseBlock();
		mainScreen->eraseShadow();
		mainScreen->turnRight();
		mainScreen->updateShadow();
		mainScreen->redrawShadow();
		mainScreen->redrawBlock();
	}
	void turnLeft() {
		mainScreen->eraseBlock();
		mainScreen->eraseShadow();
		mainScreen->turnLeft();
		mainScreen->updateShadow();
		mainScreen->redrawShadow();
		mainScreen->redrawBlock();
	}
	void dragDown() {
		while (moveDown()) Sleep(3);
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
			mainScreen->redrawShadow();
			mainScreen->redrawBlock();
			holdFlag = false;
		}
	}
	~Tetris() {
		delete mainScreen;
		delete subScreen;
		delete scoreManager;
	}
};