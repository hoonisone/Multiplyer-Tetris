#pragma once
#include <vector>
#include <string>
#include "Consol.h"

using namespace std;
using PointShape = vector<string>;
//enum Color { BLACK, BLUE ,GREEN ,AQUA ,RED ,PURPLE ,YELLOW ,WHITE ,GRAY,
//LIGHT_BLUE ,LIGHT_GREEN ,LIGHT_AQUA ,LIGHT_RED ,LIGHT_PURPLE ,LIGHT_YELLOW ,BRIGHT_WHITE
//};

class Painter;

class Painter {
protected:
	int pointWidth, pointHeight;
private:
	void adjustPointSize() {
		pointHeight = pointShape.size();
		int max = 0;
		for (int i = 0; i < pointHeight; i++) {
			max = max > pointShape[i].size() ? max : pointShape[i].size();
		}
		pointWidth = max;
	}
	void setShape(PointShape pointShape) {
		this->pointShape = pointShape;
		adjustPointSize();
	}
	void press(const int x, const int y)const {
		for (int i = 0; i < pointShape.size(); i++) {
			Consol::move(x, y + i);
			cout << pointShape[i];
		}
	}
	void _point(const int x, const int y)const {
		press(x, y);
	}
	void _horizontal(const int x, const int y, const int w)const {
		for (int i = 0; i < w; i++) {
			press(x + i * pointWidth, y);
		}
	}
	void _vertical(const int x, const int y, const int h)const {
		for (int i = 0; i < h; i++) {
			_point(x, y + i * pointHeight);
		}
	}
	void _borderRect(const int x, const int y, const int w, const int h)const {
		_horizontal(x, y, w);
		_vertical(x, y, h);
		_horizontal(x, y + (h - 1) * pointHeight, w);
		_vertical(x + (w - 1) * pointWidth, y, h);
	}
	void _rect(const int x, const int y, const int w, const int h)const {
		for (int i = 0; i < h; i++) {
			_horizontal(x, y + i, w);
		}
	}
protected:
	PointShape pointShape;
public:
	int getWidth() {
		return pointWidth;
	}
	int getHeight() {
		return pointHeight;
	}
	Painter(const Painter& painter) : Painter(painter.pointShape) {};
	Painter(const Painter* painter) : Painter(*painter) {};
	Painter(PointShape pointShape = {"*"}){
		setShape(pointShape);
	};
	virtual Painter* newObject() const {
		cout << "hello#";
		return new Painter(this);
	}
	virtual void point(int x, int y)const {
		_point(x, y);
	}
	virtual void horizontal(int x, int y, int w)const {
		_horizontal(x, y, w);
	}
	virtual void vertical(int x, int y, int h)const {
		_vertical(x, y, h);
	}
	virtual void borderRect(int x, int y, int w, int h)const {
		_borderRect(x, y, w, h);
	}
	void rect(const int x, const int y, const int w, const int h)const {
		_rect(x, y, w, h);
	}
};