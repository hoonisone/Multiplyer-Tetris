#pragma once
#include "graphic.h"
#include "block.h"
#include "Painter.h"
#include "ColorPainter.h"

class BlockBoard {
protected:
	int boardWidth, boardHeight;
	vector<vector<bool>> data;	// 음수 = 투명한 색
	bool rangeCheck(const Block* block) const {
		const BlockShape& blockShape = block->getBlockShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->x + xi;
					int ny = block->y + yi;
					if (!rangeCheck(nx, ny))
						return false;
				}
			}
		}
		return true;
	}
	bool rangeCheck(int x, int y) const {	// block이 board안에 있는가?
		return 0 <= x && x < boardWidth && 0 <= y && y < boardHeight;
	}
	bool crashCheck(const Block* block) const {	// block이 board와 충돌하는가?
		const BlockShape& blockShape = block->getBlockShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->x + xi;
					int ny = block->y + yi;
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
	BlockBoard(int boardWidth = 10, int boardHeight = 20) :boardWidth(boardWidth), boardHeight(boardHeight) {
		data = vector<vector<bool>>(boardHeight, vector<bool>(boardWidth, false));
	};
	virtual void draw(int X, int Y) {
		for (int yi = 0; yi < boardHeight; yi++) {
			for (int xi = 0; xi < boardWidth; xi++) {
				if (data[yi][xi]) {
					Painter({ "■" }).point(X+2*(X + xi),Y+ (Y + yi));
				}
			}
		}
	}
	virtual void erase(int x, int y) {
		Painter({ "  " }).rect(x, y, boardWidth, boardHeight);
	}
	virtual void press(const Block *block) {
		const BlockShape& blockShape = block->getBlockShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->x + xi;
					int ny = block->y + yi;
					data[ny][nx] = true;
				}
			}
		}
	}
};


class PaintBlockBoard : public BlockBoard {
private:
	int blockWidth, blockHeight;
	vector<vector<Painter*>> data;
	bool sizeCheck(Painter* painter) {
		return painter->getWidth() == blockWidth && painter->getHeight() == blockHeight;
	}
public:
	PaintBlockBoard(int blockWidth = 1, int blockHeight = 1, int boardWidth = 10, int boardHeight = 20) :blockWidth(blockWidth), blockHeight(blockHeight), BlockBoard(boardWidth, boardHeight) {
		data = vector<vector<Painter*>>(boardHeight, vector<Painter*>(boardWidth, NULL));
	}
	virtual void draw(int X, int Y) {
		for (int yi = 0; yi < boardHeight; yi++) {
			for (int xi = 0; xi < boardWidth; xi++) {         
				if (data[yi][xi] != NULL) {
					Painter* painter = data[yi][xi];
					painter->point(X + painter->getWidth()*xi, Y + painter->getHeight()*yi);
				}
			}
		}
	}
	virtual void press(const PaintBlock* block) {
		const BlockShape& blockShape = block->getBlockShape();
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					int nx = block->x + xi;
					int ny = block->y + yi;
					Painter* painter = block->getPainter()->newObject();// painter를 복사하여 저장
					if (!sizeCheck(painter)) {
						data[ny][nx] = painter;
					}else {
						errorPrint("painter size is worng");
					}

				}
			}
		}
	}
	~PaintBlockBoard() {
		for (int yi = 0; yi < boardHeight; yi++) {
			for (int xi = 0; xi < boardWidth; xi++) {
				if (data[yi][xi] != NULL) {
					delete data[yi][xi];
				}
			}
		}
	}
};