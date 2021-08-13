#pragma once
#include "Block.h"
#include "Painter.h"
#include "ColorPainter.h"

class BlockBoard {
protected:
	int widthNum, heightNum;	// 가로 세로 블록 개수
	int pointWidth, pointHeight;	// 블록 한 칸의 크기이며 페인터 하나가 블록 한 칸에 해당한다.
	vector<vector<Painter*>> data;	// 블록의 색과 모양을 Painter로 저장

	bool pointSizeCheck(const Painter* painter)const {	// 페인터와 보드의 블록 한 칸의 크기가 동일한지 체크  true => size 동일
		return painter->getWidth() == pointWidth && painter->getHeight() == pointHeight;
	}	
	bool rangeCheck(const int x, const int y) const {	// block이 board안에 있는가?
		return 0 <= x && x < widthNum && 0 <= y && y < heightNum;
	}
	bool crashCheck(const Block* block) const {	// block이 board와 충돌하는가?	
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
	bool permitCheck(const Block* block) const { // block의 현재 위치가 board안에서 유효한가?
		return rangeCheck(block) && !crashCheck(block);	// 범위 안에 있으면서 충돌이 없어야 한다.
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
					Painter* painter = block->getPainter()->getCopy();// painter를 복사하여 저장
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