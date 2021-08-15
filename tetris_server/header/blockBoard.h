#pragma once
#include "Block.h"
#include "Painter.h"
#include "ColorPainter.h"
#include "error.h"
class LineCounter {// 라인의 크기(원소의 개수) 만큼 체크 되었는지 확인한다.
private:
	int lineNum, elementNum;
	vector<int> data;// 각 라인에 채워진 블록의 개수를 기록 => lineClear 함수를 최적화 하기 위함
	vector<int> clearTarget;
	void pullLine() {// 모두 체크된 라인은 제거하고 앞에서 다시 추가
		for (int i = 0; i < clearTarget.size(); i++) {
			data.erase(data.begin() + clearTarget[i]);
			data.insert(data.begin(), elementNum);
		}
	}
public:
	LineCounter(int lineNum, int lineSize) :lineNum(lineNum), elementNum(lineSize) {
		data = vector<int>(lineNum, lineSize);// 각 라인마다 동일한 사이즈의 원소가 있다
	}
	void check(int y) { // 보드에 블록을 체울 때 호출하는 함수로 라인이 가득차면 기록한다. 
		int& num = data[y];
		num--;
		if (num == 0)	// 모두 소진되면 기록
			clearTarget.push_back(y);	// 기록
	}
	vector<int> getClearTarget() {	// 저장된 타겟을 반환하고 비운다.
		vector<int> clearTarget = this->clearTarget;
		pullLine();
		this->clearTarget.clear();
		return clearTarget;
	}
};
class BlockBoard {
protected:
	int drawX, drawY;
	int pointWithNum, pointHeightNum;	// 가로 세로 블록 개수
	int pointWidth, pointHeight;	// 블록 한 칸의 크기이며 페인터 하나가 블록 한 칸에 해당한다.
	int width, height;	// 커서 기준 가로세로 길이
	vector<vector<Painter*>> data;	// 블록의 색과 모양을 Painter로 저장
	LineCounter *lineCounter;

	bool pointSizeCheck(const Painter* painter)const {	// 페인터와 보드의 블록 한 칸의 크기가 동일한지 체크  true => size 동일
		return painter->getWidth() == pointWidth && painter->getHeight() == pointHeight;
	}	
	bool rangeCheck(const int x, const int y) const {	// block이 board안에 있는가?
		return 0 <= x && x < pointWithNum && 0 <= y && y < pointHeightNum;
	}
	bool crashCheck(const Block* block) const {	// block이 board와 충돌하는가?	
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
	bool permitCheck(const Block* block) const { // block의 현재 위치가 board안에서 유효한가?
		return rangeCheck(block) && !crashCheck(block);	// 범위 안에 있으면서 충돌이 없어야 한다.
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
					Painter* painter = block->getPainter()->getCopy();// painter를 복사하여 저장
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
	int getWidth()const {// 커서 기준 board의 가로 길이
		return width;
	}
	int getHeight()const {
		return height;
	}
	int getPointWidhtNum()const {
		return pointWithNum;
	}   // point기준 board의 가로 길이
	int getPointHeightNum()const {
		return pointHeightNum;
	}
	//int getPointWidth()const {
	//	return pointWidth;
	//}	// board에서 다루는 블록 포인터 하나에 대한 가로 길이
	int getPointHeight()const {
		return pointHeight;
	}
	int clearLine() {	// 다 채워진 줄을 지우고 지워진 줄 개수를 반환
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