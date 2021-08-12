#pragma once
#include <stdio.h>
#include <windows.h>
#include "Painter.h"
#include "ColorPainter.h"
#define BLOCK_WIDTH 4
#define BLOCK_HEIGHT 4

enum BlockShapeName { O, I, Z, S, L, J, T };
using BlockShape = vector<vector<bool>>;
using Angle = int;
static const vector<vector<BlockShape>> blockShapes = {
		{{{0,0,0,0}, //O
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
		{{{0,0,0,0}, //I
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
		{{{0,0,0,0}, //Z
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
		{{{0,0,0,0}, //S
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
		{{{0,1,0,0}, //L
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
		{{{0,0,1,0}, //J
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
		{{{0,1,0,0}, //T
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
	BlockShapeName shape;
	Angle angle;
public:
	int x, y;
	Block(int x, int y, BlockShapeName shape, Angle angle) :x(x), y(y), shape(shape), angle(angle) {};
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
	virtual void draw(int X, int Y) {
		BlockShape const &blockShape = blockShapes[shape][angle];
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					Painter({ "бс" }).point(X+x+2*xi,Y+y+yi);
				}
			}
		}
	}
	virtual void erase() {
		Painter({ "        ", "        ", "        ", "        " }).point(x, y);
	}
	const BlockShape& getBlockShape() const{
		return blockShapes[shape][angle];
	}
};

class PaintBlock : public Block {
private:
	ColorPainter* painter;
public:
	PaintBlock(int x, int y, BlockShapeName shape, Angle angle, ColorPainter* painter): Block(x, y, shape, angle), painter(painter) {};
	virtual void draw(int X, int Y) override {
		BlockShape const& blockShape = blockShapes[shape][angle];
		for (int yi = 0; yi < BLOCK_HEIGHT; yi++) {
			for (int xi = 0; xi < BLOCK_WIDTH; xi++) {
				if (blockShape[yi][xi]) {
					painter->point(X+(x + xi)*painter->getWidth(), Y+(y + yi)*painter->getHeight());
				}
			}
		}
	}
	Color getColor() const{
		return painter->getPointColor();
	}
	Painter* getPainter() const {
		return painter;
	}
	virtual void erase() {
		Painter({ "  " }).rect(x * painter->getWidth(), y * painter->getHeight(), BLOCK_WIDTH * painter->getWidth(), BLOCK_HEIGHT * painter->getHeight());
	}
	~PaintBlock() {
		delete painter;
	}
};