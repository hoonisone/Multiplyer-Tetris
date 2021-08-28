#pragma once
#include "MainScreen.h"
#include "SubScreen.h"
#include "BlockCreator.h"
#include "scoreManager.h"
#include "Timer.h"
#include <algorithm>

class Tetris {
private:
	int drawX, drawY;
	Timer* timer;
	MainScreen* mainScreen;
	SubScreen* subScreen;
	BlockCreator* creator;
	ScoreManager* scoreManager;
	bool endFlag = false;
	bool holdFlag = true;
	void press() {
		Block* next = subScreen->changeNext(creator->createBlock());	// 새 블록을 주고 등록되어 있던 next 블록을 얻어온다.
		mainScreen->press(next);
		holdFlag = true;
	}
	bool checkPermit() {
		return mainScreen->checkPermit();
	}
	int getLevel() {
		return scoreManager->getLevel();
	}
public:
	Tetris(MainScreen* mainScreen, SubScreen* subScreen, BlockCreator* creator, ScoreManager * scoreManager) : mainScreen(mainScreen), subScreen(subScreen), creator(creator), scoreManager(scoreManager){
		timer = new Timer();
	};
	void draw(int x, int y) {
		drawX = x;
		drawY = y;
		drawScoreBoard();
		drawMainScreen();
		drawSubScreen();
	}
	void update() {
		static int accTime = 0;
		accTime += timer->getAccTime();
		timer->init();
		if (accTime > updateSpeed()) {
			accTime -= updateSpeed();
			moveDown();
		}
	}
	int getWidth() {
		return mainScreen->getWidth() + subScreen->getWidth()-1;
	}
	int updateSpeed() {
		return max(1000 - 50 * getLevel(), 150);
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
	int moveDown() {	// 이동 성공여부 반환
		mainScreen->eraseShadow();
		mainScreen->eraseBlock();
		bool succesFlag = mainScreen->moveDown();
		if (!succesFlag){	// 바닥에 닿았다면
			press();
			if (endFlag) {
				return succesFlag;
			}
			scoreManager->addBlock(1);	// 점수 추가(블록 한 개)
			int lineClearNum = mainScreen->clearLine();	// 완성된 라인 지우기 & 지워진 개수 반환
			if(lineClearNum>0){
				scoreManager->addLine(lineClearNum);	// 점수 추가(라인 n개)
			};
			if (!checkPermit()) {	// 게임 종료 체크
				endFlag = true;
				mainScreen->redrawBoard();
				return succesFlag;
			}
			scoreManager->redrawContent();
			mainScreen->eraseBoard();
		}
		mainScreen->updateShadow();
		mainScreen->redrawBoard();	// 보드 다시 그리기
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
	bool checkEnd() {
		return endFlag;
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