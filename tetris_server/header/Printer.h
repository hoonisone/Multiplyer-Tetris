#pragma once
#include <vector>
#include <string>
#include "Consol.h"

enum AlignX { LEFT, CENTER, RIGHT };
enum AlignY { TOP, MIDDLE, BOTTOM };

using namespace std;

class Printer {
protected:
	AlignX alignX;
	AlignY alignY;
private:
	void printText(int x, int y, string text)const {
		Consol::move(x, y);
		cout << text;
	}
	int getPrintPosX(int x, int w, int len, AlignX align)const {
		switch (align) {
		case LEFT:
			return x;
		case CENTER:
			return x + (w - len) / 2;
		case RIGHT:
			return x + (w - len);
		}
	}
	int getPrintPosY(int y, int h, int n, AlignY align)const {
		return getPrintPosX(y, h, n, (AlignX)align);
	}
public:
	Printer(const Printer& object) : Printer(object.alignX, object.alignY) {}
	Printer(const Printer* object) : Printer(*object) {}
	Printer(AlignX alignX = LEFT, AlignY alignY = MIDDLE) :
		alignX(alignX), alignY(alignY) {
	}
	virtual Printer* newObject() const {
		return new Printer(this);
	}
	void setAlign(AlignX alignX, AlignY alignY) {
		this->alignX = alignX;
		this->alignY = alignY;
	}
	virtual void printText(int x, int y, int w, int h, vector<string> tokens) const{
		int Y = getPrintPosY(y, h, tokens.size(), alignY);
		int X;
		for (int i = 0; i < tokens.size(); i++) {
			X = getPrintPosX(x, w, tokens[i].size(), alignX);
			printText(X, Y + i, tokens[i]);
		}

	}
};