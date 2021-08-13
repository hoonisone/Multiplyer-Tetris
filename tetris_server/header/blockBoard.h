#pragma once
#include "Block.h"
#include "Painter.h"
#include "ColorPainter.h"

class BlockBoard {
protected:
	int widthNum, heightNum;	// ���� ���� ��� ����
	int pointWidth, pointHeight;	// ��� �� ĭ�� ũ���̸� ������ �ϳ��� ��� �� ĭ�� �ش��Ѵ�.
	vector<vector<Painter*>> data;	// ����� ���� ����� Painter�� ����

	bool pointSizeCheck(const Painter* painter)const {	// �����Ϳ� ������ ��� �� ĭ�� ũ�Ⱑ �������� üũ  true => size ����
		return painter->getWidth() == pointWidth && painter->getHeight() == pointHeight;
	}	
	bool rangeCheck(const int x, const int y) const {	// block�� board�ȿ� �ִ°�?
		return 0 <= x && x < widthNum && 0 <= y && y < heightNum;
	}
	bool crashCheck(const Block* block) const {	// block�� board�� �浹�ϴ°�?	
		const BlockShape& blockShape = block->getShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->getX() + xi;
					int ny = block->getY() + yi;
					if (rangeCheck(nx, ny)) {
						if (data[ny][nx])
							return true;
					}
				}
			}
		}
		return true;
	}
	bool permitCheck(const Block* block) const { // block�� ���� ��ġ�� board�ȿ��� ��ȿ�Ѱ�?
		return rangeCheck(block) && !crashCheck(block);	// ���� �ȿ� �����鼭 �浹�� ����� �Ѵ�.
	}
public:
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
	BlockBoard(int pointWidth = 2, int pointHeight = 1, int widhtNum = 10, int heightNum = 20) :pointWidth(pointWidth), pointHeight(pointHeight), widthNum(widhtNum), heightNum(heightNum) {
		data = vector<vector<Painter*>>(heightNum, vector<Painter*>(widhtNum, NULL));
	};
	virtual void draw(const int X, const int Y)const {
		for (int yi = 0; yi < heightNum; yi++) {
			for (int xi = 0; xi < widthNum; xi++) {
				if (data[yi][xi] != NULL) {
					Painter* painter = data[yi][xi];
					painter->point(X + painter->getWidth() * xi, Y + painter->getHeight() * yi);
				}
			}
		}
	}
	virtual void erase(const int x, const int y)const {
		Painter({ "  " }).rect(x, y, widthNum, heightNum);
	}
	virtual void press(const Block *block) {
		if (!pointSizeCheck(block->getPainter())) {
			
		}
		const BlockShape& blockShape = block->getShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->getX() + xi;
					int ny = block->getY() + yi;
					Painter* painter = block->getPainter()->getCopy();// painter�� �����Ͽ� ����
					if (!pointSizeCheck(painter)) {
						data[ny][nx] = painter;
					}
					else {
						errorPrint("painter size is worng");
					}

				}
			}
		}
	}
	pair<int, int> getBlockSize()const {
		return make_pair(pointWidth, pointHeight);
	}
	pair<int, int> getBoardSize()const {
		return make_pair(widthNum, heightNum);
	}
	int getWidhtNum()const {
		return widthNum;
	}
	int getHeightNum()const {
		return heightNum;
	}
	int getPointWidth()const {
		return pointWidth;
	}
	int getPointHeight()const {
		return pointHeight;
	}
	~BlockBoard() {
		for (int yi = 0; yi < heightNum; yi++) {
			for (int xi = 0; xi < widthNum; xi++) {
				if (data[yi][xi] != NULL) {
					delete data[yi][xi];
				}
			}
		}
	}
};