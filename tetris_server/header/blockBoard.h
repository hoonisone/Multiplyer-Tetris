#pragma once
#include "Block.h"
#include "Painter.h"
#include "ColorPainter.h"
#include "error.h"
class LineCounter {// ������ ũ��(������ ����) ��ŭ üũ �Ǿ����� Ȯ���Ѵ�.
private:
	int lineNum, elementNum;
	vector<int> data;// �� ���ο� ä���� ����� ������ ��� => lineClear �Լ��� ����ȭ �ϱ� ����
	vector<int> clearTarget;
	void pullLine() {// ��� üũ�� ������ �����ϰ� �տ��� �ٽ� �߰�
		for (int i = 0; i < clearTarget.size(); i++) {
			data.erase(data.begin() + clearTarget[i]);
			data.insert(data.begin(), elementNum);
		}
	}
public:
	LineCounter(int lineNum, int lineSize) :lineNum(lineNum), elementNum(lineSize) {
		data = vector<int>(lineNum, lineSize);// �� ���θ��� ������ �������� ���Ұ� �ִ�
	}
	void check(int y) { // ���忡 ����� ü�� �� ȣ���ϴ� �Լ��� ������ �������� ����Ѵ�. 
		int& num = data[y];
		num--;
		if (num == 0)	// ��� �����Ǹ� ���
			clearTarget.push_back(y);	// ���
	}
	vector<int> getClearTarget() {	// ����� Ÿ���� ��ȯ�ϰ� ����.
		vector<int> clearTarget = this->clearTarget;
		pullLine();
		this->clearTarget.clear();
		return clearTarget;
	}
};
class BlockBoard {
protected:
	int drawX, drawY;
	int pointWithNum, pointHeightNum;	// ���� ���� ��� ����
	int pointWidth, pointHeight;	// ��� �� ĭ�� ũ���̸� ������ �ϳ��� ��� �� ĭ�� �ش��Ѵ�.
	int width, height;	// Ŀ�� ���� ���μ��� ����
	vector<vector<Painter*>> data;	// ����� ���� ����� Painter�� ����
	LineCounter *lineCounter;

	bool pointSizeCheck(const Painter* painter)const {	// �����Ϳ� ������ ��� �� ĭ�� ũ�Ⱑ �������� üũ  true => size ����
		return painter->getWidth() == pointWidth && painter->getHeight() == pointHeight;
	}	
	bool rangeCheck(const int x, const int y) const {	// block�� board�ȿ� �ִ°�?
		return 0 <= x && x < pointWithNum && 0 <= y && y < pointHeightNum;
	}
	bool crashCheck(const Block* block) const {	// block�� board�� �浹�ϴ°�?	
		const BlockShape& blockShape = block->getShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->getX() + xi;
					int ny = block->getY() + yi;
					if (rangeCheck(nx, ny)) {
						if (data[ny][nx] != NULL)
							return true;
					}
				}
			}
		}
		return false;
	}
	void eraseLine(int y) {
		data.erase(data.begin() + y);
		data.insert(data.begin(), vector<Painter*>(pointWithNum, NULL));
	}
	virtual void press(int x, int y, Painter* painter) {
		data[y][x] = painter;
		lineCounter->check(y);
	}
	virtual void drawPointSetting(const int drawX, const int drawY){
		this->drawX = drawX;
		this->drawY = drawY;
	}
public:
	bool permitCheck(const Block* block) const { // block�� ���� ��ġ�� board�ȿ��� ��ȿ�Ѱ�?
		return rangeCheck(block) && !crashCheck(block);	// ���� �ȿ� �����鼭 �浹�� ����� �Ѵ�.
	}
	bool rangeCheck(const Block* block) const {
		const BlockShape& blockShape = block->getShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->getX() + xi;
					int ny = block->getY() + yi;
					if (!rangeCheck(nx, ny))
						return false;
				}
			}
		}
		return true;
	}
	BlockBoard(int pointWidth = 2, int pointHeight = 1, int pointWithNum = 10, int pointHeightNum = 20) :pointWidth(pointWidth), pointHeight(pointHeight), pointWithNum(pointWithNum), pointHeightNum(pointHeightNum) {
		data = vector<vector<Painter*>>(pointHeightNum, vector<Painter*>(pointWithNum, NULL));
		lineCounter = new LineCounter(pointHeightNum, pointWithNum);
		width = pointWithNum * pointWidth;
		height = pointHeightNum * pointHeight;
	};
	virtual void draw(const int drawX, const int drawY) {
		drawPointSetting(drawX, drawY);
		redraw();
	}
	virtual void redraw() {
		for (int yi = 0; yi < pointHeightNum; yi++) {
			for (int xi = 0; xi < pointWithNum; xi++) {
				if (data[yi][xi] != NULL) {
					Painter* painter = data[yi][xi];
					painter->point(drawX + painter->getWidth() * xi, drawY + painter->getHeight() * yi);
				}
			}
		}
	}
	virtual void erase()const {
		Painter({ "  " }).rect(drawX, drawY, pointWithNum, pointHeightNum);
	}
	virtual void press(const Block *block) {
		if (!pointSizeCheck(block->getPainter())) {
			errorPrint("painter size is worng");
		}
		const BlockShape& blockShape = block->getShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->getX() + xi;
					int ny = block->getY() + yi;
					Painter* painter = block->getPainter()->getCopy();// painter�� �����Ͽ� ����
					press(nx, ny, painter);
				}
			}
		}
	}

	pair<int, int> getBlockSize()const {
		return make_pair(pointWidth, pointHeight);
	}
	pair<int, int> getBoardSize()const {
		return make_pair(pointWithNum, pointHeightNum);
	}
	int getWidth()const {// Ŀ�� ���� board�� ���� ����
		return width;
	}
	int getHeight()const {
		return height;
	}
	int getPointWidhtNum()const {
		return pointWithNum;
	}   // point���� board�� ���� ����
	int getPointHeightNum()const {
		return pointHeightNum;
	}
	//int getPointWidth()const {
	//	return pointWidth;
	//}	// board���� �ٷ�� ��� ������ �ϳ��� ���� ���� ����
	int getPointHeight()const {
		return pointHeight;
	}
	int clearLine() {	// �� ä���� ���� ����� ������ �� ������ ��ȯ
		vector<int> target = lineCounter->getClearTarget();
		for (int i = 0; i < target.size(); i++) {
			eraseLine(target[i]);
		}
		return target.size();
	}
	~BlockBoard() {
		for (int yi = 0; yi < pointHeightNum; yi++) {
			for (int xi = 0; xi < pointWithNum; xi++) {
				if (data[yi][xi] != NULL) {
					delete data[yi][xi];
				}
			}
		}
		delete lineCounter;
	}
};