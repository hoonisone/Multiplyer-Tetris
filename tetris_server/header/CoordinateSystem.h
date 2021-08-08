#pragma once
#include <iostream>
#include <windows.h>

#define CURSOR createCuusor()
#define POINT createPoint()

using namespace std;

class CoordinateSystem {
private:
	int x_scale, y_scale;
public:
	CoordinateSystem(int x_scale, int y_scale) : x_scale(x_scale), y_scale(y_scale) {};
	void move(int x, int y);
	static pair<int, int> getCoordinate();
};
CoordinateSystem& createCuusor();
CoordinateSystem& createPoint();