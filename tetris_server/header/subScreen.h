#pragma once
#include "Block.h"
#include "ColorPainter.h"
#include "ColorPrinter.h"
class SubScreen {
private:
	int drawX, drawY;
	int width, height;
	Block* next;
	Block* hold= NULL;
	ColorPainter* painter;
	void drawBorder() {
		painter->rectBorder(drawX, drawY, width, height, CURSOR_STD);
	}
	void drawNextName() {
		ColorPrinter(CENTER, MIDDLE).printText(drawX, drawY + painter->getHeight(), width, 1, { "N E X T" });
	}
	void drawNext() {
		next->draw(drawX + painter->getWidth(), drawY + painter->getHeight() + 1);
	}
	void eraseNext() {
		next->erase();
	}
	void drawHoldName() {
		ColorPrinter(CENTER, MIDDLE).printText(drawX, drawY + painter->getHeight() + 1 + next->getHeight(), width, 1, { "H O L D" });
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
	SubScreen(int width, int height, Block* next, ColorPainter *painter) : width(width), height(height), next(next), painter(painter){};
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
	Block* changeHold(Block * block) {	// ���ڷ� ���� ��ϰ� hold�� ��ȯ�Ѵ�. �̶� ��ȯ�� hold�� NULL�� �� �ִ�.(ó������ ����ֱ� ����)
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