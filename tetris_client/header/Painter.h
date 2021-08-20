#pragma once
#include <vector>
#include <string>
#include "Consol.h"

using namespace std;
enum PaintStd {POINT_STD=0, CURSOR_STD=1};	// 입력된 매개변수의 크기를 포인터의 개수 또는 커서의 개수로 본다.
using PointElement = string;
using PointShape = vector<string>;
//enum Color { BLACK, BLUE ,GREEN ,AQUA ,RED ,PURPLE ,YELLOW ,WHITE ,GRAY,
//LIGHT_BLUE ,LIGHT_GREEN ,LIGHT_AQUA ,LIGHT_RED ,LIGHT_PURPLE ,LIGHT_YELLOW ,BRIGHT_WHITE
//};
std::string operator*(std::string str, int n) {
	string s;
	for (int i = 0; i < n; i++) {
		s += str;
	}
	return s;
}

class Painter {
protected:
	PointShape pointShape;
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
	void _rectBorder(const int x, const int y, const int w, const int h)const {
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
	int toPointWidthNum(int cursorWidthNum) const{
		return cursorWidthNum / pointWidth;
	}
	int toPointHeightNum(int cursorHeightNum) const{
		return cursorHeightNum / pointHeight;
	}
public:
	bool checkPointSize(Painter* painter)const {	//point 사이즈가 동일한가?
		return this->pointWidth == painter->pointWidth && this->pointHeight == painter->pointHeight;
	}
	Painter(const Painter& painter) : Painter(painter.pointShape) {};
	Painter(const Painter* painter) : Painter(*painter) {};
	Painter(PointShape pointShape = { "*" }) {
		setShape(pointShape);
	};
	int getWidth() const {
		return pointWidth;
	}
	int getHeight() const {
		return pointHeight;
	}
	virtual Painter* getCopy() const {
		return new Painter(this);
	}
	virtual void point(int x, int y)const {
		_point(x, y);
	}
	virtual void horizontal(int x, int y, int w, PaintStd standard = POINT_STD)const {
		switch ((int)standard) {
		case POINT_STD:
			_horizontal(x, y, w);
			break;
		case CURSOR_STD:
			_horizontal(x, y, toPointWidthNum(w));
			break;
		}
	}
	virtual void vertical(int x, int y, int h, PaintStd standard = POINT_STD)const {
		switch ((int)standard) {
		case POINT_STD:
			_vertical(x, y, h);
			break;
		case CURSOR_STD:
			_vertical(x, y, toPointHeightNum(h));
			break;
		}
	}
	virtual void rectBorder(int x, int y, int w, int h, PaintStd standard = POINT_STD)const {
		switch ((int)standard) {
		case POINT_STD:
			_rectBorder(x, y, w, h);
			break;
		case CURSOR_STD:
			_rectBorder(x, y, toPointWidthNum(w), toPointHeightNum(h));
			break;
		}
	}
	void rect(const int x, const int y, const int w, const int h, PaintStd standard = POINT_STD)const {
		switch ((int)standard) {
		case POINT_STD:
			_rect(x, y, w, h);
			break;
		case CURSOR_STD:
			_rect(x, y, toPointWidthNum(w), toPointHeightNum(h));
			break;
		}
	}
	virtual Painter* getEraser() {
		PointShape shape = PointShape(pointHeight, string(pointWidth, ' '));
		return new Painter(shape);
	}

	void changeAllPointShapeElementInto(PointElement element) {
		PointShape newShape;
		for (int i = 0; i < pointShape.size(); i++) {
			newShape.push_back(element*(pointShape[i].size()/element.size()));
		} 
		pointShape = newShape;
	}
};