#pragma once
#include "Block.h"
#include "Painter.h"
#include "ColorPainter.h"

class BlockBoard {
protected:
	int boardWidth, boardHeight;
	int pointWidth, pointHeight;	// ��� �� ĭ�� ũ���̸� ������ �ϳ��� ��� �� ĭ�� �ش��Ѵ�.
	vector<vector<Painter*>> data;	// ����� ���� ����� Painter�� ����

	bool pointSizeCheck(const Painter* painter)const {	// �����Ϳ� ������ ��� �� ĭ�� ũ�Ⱑ �������� üũ  true => size ����
		return painter->getWidth() == pointWidth && painter->getHeight() == pointHeight;
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
	bool rangeCheck(const int x, const int y) const {	// block�� board�ȿ� �ִ°�?
		return 0 <= x && x < boardWidth && 0 <= y && y < boardHeight;
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
	BlockBoard(int pointWidth = 2, int pointHeight = 1, int boardWidth = 10, int boardHeight = 20) :pointWidth(pointWidth), pointHeight(pointHeight), boardWidth(boardWidth), boardHeight(boardHeight) {
		data = vector<vector<Painter*>>(boardHeight, vector<Painter*>(boardWidth, NULL));
	};
	virtual void draw(const int X, const int Y)const {
		for (int yi = 0; yi < boardHeight; yi++) {
			for (int xi = 0; xi < boardWidth; xi++) {
				if (data[yi][xi] != NULL) {
					Painter* painter = data[yi][xi];
					painter->point(X + painter->getWidth() * xi, Y + painter->getHeight() * yi);
				}
			}
		}
	}
	virtual void erase(const int x, const int y)const {
		Painter({ "  " }).rect(x, y, boardWidth, boardHeight);
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
					Painter* painter = block->getPainter()->newObject();// painter�� �����Ͽ� ����
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
		return make_pair(boardWidth, boardHeight);
	}
	int getBoardWidth()const {
		return boardWidth;
	}
	int getBoardHeight()const {
		return boardHeight;
	}
	int getPointWidth()const {
		return pointWidth;
	}
	int getPointHeight()const {
		return pointHeight;
	}
	~BlockBoard() {
		for (int yi = 0; yi < boardHeight; yi++) {
			for (int xi = 0; xi < boardWidth; xi++) {
				if (data[yi][xi] != NULL) {
					delete data[yi][xi];
				}
			}
		}
	}
};