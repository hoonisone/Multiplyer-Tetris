#pragma once
#include <iostream>
#include <windows.h>

#define CURSOR CoordinateSystem(1, 1)
#define POINT CoordinateSystem(2, 1)

using namespace std;

class CoordinateSystem {
private:
	int x_scale, y_scale;
public:
	CoordinateSystem(int x_scale, int y_scale) : x_scale(x_scale), y_scale(y_scale) {};
	void move(int x, int y);
	static pair<int, int> getCoordinate();
};