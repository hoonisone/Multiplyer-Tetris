#pragma once
#include <stdio.h>
#include <windows.h>
#include "Painter.h"
#include "ColorPainter.h"
#include "Random.h"
#define BLOCK_WIDTH 4
#define BLOCK_HEIGHT 4
#define BLOCK_SHAPE_NUM 7
#define BLOCK_ANGLE_NUM 4


enum BlockName { o, i, z, s, l, j, t };
using BlockShape = vector<vector<bool>>;
using BlockAngle = int;
static const vector<vector<BlockShape>> blockShapeData = {
		{{{0,0,0,0}, //o
		  {0,1,1,0},
		  {0,1,1,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,1,0},
		  {0,1,1,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,1,0},
		  {0,1,1,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,1,0},
		  {0,1,1,0},
		  {0,0,0,0}}},
		{{{0,0,0,0}, //i
		  {1,1,1,1},
		  {0,0,0,0},
		  {0,0,0,0}},
		 {{0,1,0,0},
		  {0,1,0,0},
		  {0,1,0,0},
		  {0,1,0,0}},
		 {{0,0,0,0},
		  {1,1,1,1},
		  {0,0,0,0},
		  {0,0,0,0}},
		 {{0,1,0,0},
		  {0,1,0,0},
		  {0,1,0,0},
		  {0,1,0,0}}},
		{{{0,0,0,0}, //z
		  {1,1,0,0},
		  {0,1,1,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,0,1,0},
		  {0,1,1,0},
		  {0,1,0,0}},
		 {{0,0,0,0},
		  {1,1,0,0},
		  {0,1,1,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,0,1,0},
		  {0,1,1,0},
		  {0,1,0,0}} },
		{{{0,0,0,0}, //s
		  {0,1,1,0},
		  {1,1,0,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,0,0},
		  {0,1,1,0},
		  {0,0,1,0}},
		 {{0,0,0,0},
		  {0,1,1,0},
		  {1,1,0,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,0,0},
		  {0,1,1,0},
		  {0,0,1,0}} },
		{{{0,1,0,0}, //l
		  {0,1,0,0},
		  {0,1,1,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,1,1},
		  {0,1,0,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,1,0},
		  {0,0,1,0},
		  {0,0,1,0}},
		 {{0,0,0,0},
		  {0,0,1,0},
		  {1,1,1,0},
		  {0,0,0,0}} },
		{{{0,0,1,0}, //j
		  {0,0,1,0},
		  {0,1,1,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,0,0},
		  {0,1,1,1},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {0,1,1,0},
		  {0,1,0,0},
		  {0,1,0,0}},
		 {{0,0,0,0},
		  {1,1,1,0},
		  {0,0,1,0},
		  {0,0,0,0}}},
		{{{0,1,0,0}, //t
		  {1,1,1,0},
		  {0,0,0,0},
		  {0,0,0,0}},
		 {{0,1,0,0},
		  {0,1,1,0},
		  {0,1,0,0},
		  {0,0,0,0}},
		 {{0,0,0,0},
		  {1,1,1,0},
		  {0,1,0,0},
		  {0,0,0,0}},
		 {{0,1,0,0},
		  {1,1,0,0},
		  {0,1,0,0},
		  {0,0,0,0}}} };

class Block {
protected:
	int x, y;
	ColorPainter* painter;	// 블록의 출력형태를 결정(점의 모양, 색)
	BlockName name;
	BlockAngle angle;
public:
	Block(int x, int y, BlockName name, BlockAngle angle, ColorPainter* painter) :x(x), y(y), name((BlockName)((int)name% BLOCK_SHAPE_NUM)), angle(angle% BLOCK_ANGLE_NUM), painter(painter) {};
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	virtual void moveTo(int x, int y) {
		this->x = x;
		this->y = y;
	}
	virtual void moveUp() {
		y--;
	}
	virtual void moveDown() {
		y++;
	}
	virtual void moveRight() {
		x++;
	}
	virtual void moveLefe() {
		x--;
	}
	virtual void turnRight() {
		angle = (angle + 1) % 4;
	}
	virtual void turnLeft() {
		angle = (angle + 3) % 4;
	}
	virtual void draw(int X, int Y) const{
		BlockShape const& blockshape = blockShapeData[name][angle];
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockshape[yi][xi]) {
					painter->point(X + (x + xi) * painter->getWidth(), Y + (y + yi) * painter->getHeight());
				}
			}
		}
	}
	virtual void erase(int x, int y) {
		ColorPainter({" "}).rect(x+x, y+y, BLOCK_WIDTH*painter->getWidth(), BLOCK_HEIGHT*painter->getHeight());
	}
	const ColorPainter* getPainter() const {
		return painter;
	}
	const BlockShape& getShape() const {
		return blockShapeData[name][angle];
	}
	~Block() {
		delete painter;
	}

};