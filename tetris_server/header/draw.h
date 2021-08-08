#pragma once
#include "CoordinateSystem.h"
#include "Pencil.h"

class Draw {
private:
	CoordinateSystem coordinateSystem;
	Pencil pencil;
public:
	void horizontal(int x, int y, int width);
	void vertical(int x, int y, int height);
	void rect(int x, int y, int width, int height);
};


void Draw::rect(int x, int y, int width, int height) {
	horizontal(x, y, width);
	vertical(x, y, height);
	horizontal(x, y + height - 1, width);
	vertical(x + width - 1, y, height);
}