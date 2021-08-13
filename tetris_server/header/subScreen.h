#pragma once
#include "Block.h"
#include "ColorPainter.h"
#include "ColorPrinter.h"
class SubScreen {
private:
	int drawX, drawY;
	int pointWidthNum, pointHeightNum;
	Block* next;
	Block* hold= NULL;
	ColorPainter* painter;
	void drawBorder() {
		painter->rectBorder(drawX, drawY, pointWidthNum / painter->getWidth(), pointHeightNum / painter->getHeight());
	}
	void drawNextName() {
		ColorPrinter(CENTER, MIDDLE).printText(drawX, drawY + painter->getHeight(), pointWidthNum, 1, { "N E X T" });
	}
	void drawNext() {
		next->draw(drawX + painter->getWidth(), drawY + painter->getHeight() + 1);
	}
	void eraseNext() {
		next->erase();
	}
	void drawHoldName() {
		ColorPrinter(CENTER, MIDDLE).printText(drawX, drawY + painter->getHeight() + 1 + next->getHeight(), pointWidthNum, 1, { "H O L D" });
	}
	void drawHold() {
		if(hold != NULL)
			hold->draw(drawX + painter->getWidth(), drawY + painter->getHeight() + 1 + next->getHeight()+1);
	}
	void eraseHold() {
		if (hold != NULL)
			hold->erase(drawX + painter->getWidth(), drawY + painter->getHeight() + 1 + next->getHeight() + 1);
	}
public:
	SubScreen(int pointWidthNum, int pointHeightNum, Block* next, ColorPainter *painter) : pointWidthNum(pointWidthNum), pointHeightNum(pointHeightNum), next(next), painter(painter){};
	void draw(int x, int y) {
		drawX = x;
		drawY = y;
		drawBorder();
		drawNextName();
		drawNext();
		drawHoldName();
		drawHold();
	}
	Block* changeNext(Block* next) {
		Block* temp = this->next;
		eraseNext();
		this->next = next;
		drawNext();
		return temp;
	}
	Block* changeHold(Block * block) {	// 인자로 받은 블록과 hold를 교환한다. 이때 교환된 hold가 NULL일 수 있다.(처음에는 비어있기 때문)
		if (block == NULL) {
			errorPrint("null error");
		}
		block->moveTo(0, 0);
		Block* hold = this->hold;
		eraseHold();
		this->hold = block;
		drawHold();
		return hold;
	}
};