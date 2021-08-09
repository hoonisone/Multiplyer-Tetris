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
private:
	PointShape pointShape;
	Color pointColor, backgroundColor;
	void setting(Color textColor, Color backgroundColor) {
		Consol::changeTextColor(textColor);
		Consol::changeBackgroundColor(backgroundColor);
	}
	void adjustPointSize() {
		ph = pointShape.size();
		int max = 0;
		for (int i = 0; i < ph; i++) {
			max = max > pointShape[i].size() ? max : pointShape[i].size();
		}
		pw = max;
	}
	void setShape(PointShape pointShape) {
		this->pointShape = pointShape;
		adjustPointSize();
	}
	void press(int x, int y, Color pointColor, Color backgroundColor) {
		setting(pointColor, backgroundColor);
		for (int i = 0; i < pointShape.size(); i++) {
			Consol::move(x, y + i);
			cout << pointShape[i];
		}
	}
public:
	int pw, ph;
	Painter(PointShape pointShape = {"*"}, Color pointColor = WHITE, Color backgroundColor = BLACK) :pointShape(pointShape), pointColor(pointColor), backgroundColor(backgroundColor) {
		adjustPointSize();
	};
	void setColor(Color pointColor, Color bacgroundColor) {
		this->pointColor = pointColor;
		this->backgroundColor = backgroundColor;
	}	// pencil의 컬러를 설정하는 것으로 콜솔의 색을 설정하는 것과는 별개
	void point(int x, int y) {
		point(x, y, pointColor, backgroundColor);
	}
	void point(int x, int y, Color pointColor, Color backgroundColor) {
		press(x, y, pointColor, backgroundColor);
	}
	void horizontal(int x, int y, int w) {
		horizontal(x, y, w, pointColor, backgroundColor);
	}
	void horizontal(int x, int y, int w, Color pointColor, Color backgroundColor) {
		for (int i = 0; i < w; i++) {
			press(x + i * pw, y, pointColor, backgroundColor);
		}
	}
	void vertical(int x, int y, int h) {
		vertical(x, y, h, pointColor, backgroundColor);
	}
	void vertical(int x, int y, int h, Color pointColor, Color backgroundColor) {
		for (int i = 0; i < h; i++) {
			point(x, y + i * ph, pointColor, backgroundColor);
		}
	}
	void rect(int x, int y, int w, int h) {
		rect(x, y, w, h, pointColor, backgroundColor);
	}
	void rect(int x, int y, int w, int h, Color pointColor, Color backgroundColor) {
		horizontal(x, y, w, pointColor, backgroundColor);
		vertical(x, y, h, pointColor, backgroundColor);
		horizontal(x, y + (h - 1) * ph, w, pointColor, backgroundColor);
		vertical(x + (w - 1) * pw, y, h, pointColor, backgroundColor);
	}
};