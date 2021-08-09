#pragma once
#include <vector>
#include <string>
#include "Consol.h"
#include "CoordinateSystem.h"

using namespace std;
using Shape = vector<string>;
//enum Color { BLACK, BLUE ,GREEN ,AQUA ,RED ,PURPLE ,YELLOW ,WHITE ,GRAY,
//LIGHT_BLUE ,LIGHT_GREEN ,LIGHT_AQUA ,LIGHT_RED ,LIGHT_PURPLE ,LIGHT_YELLOW ,BRIGHT_WHITE
//};

class Pencil;
static Pencil* usingPencil;

class Pencil {
private:
	Shape textShape;
	Color textColor, backgroundColor;
	void setting() {
		if (usingPencil == nullptr || usingPencil != this) {
			usingPencil = this;
			Consol::changeTextColor(textColor);
			Consol::changeBackgroundColor(backgroundColor);
		}
	}
public: 

	Pencil(Shape textShape, Color textColor, Color backgroundColor) :textShape(textShape), textColor(textColor), backgroundColor(backgroundColor) {};

	void press() {
		setting();
		pair<int, int> curPosition = CoordinateSystem::getCoordinate();
		int X = curPosition.first;
		int Y = curPosition.second;
		for (int i = 0; i < textShape.size(); i++) {
			CURSOR.move(X, Y + i);
			cout << textShape[i];
		}
	}

};

