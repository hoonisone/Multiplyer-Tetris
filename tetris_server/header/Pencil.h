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
	void setting();
public: 
	Pencil(Shape textShape, Color textColor, Color backgroundColor);
	void press();
};

