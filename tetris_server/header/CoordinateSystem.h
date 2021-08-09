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
	void move(int x, int y) {
		COORD pos = { x_scale * x, y_scale * y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	static pair<int, int> getCoordinate() {
		CONSOLE_SCREEN_BUFFER_INFO a;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
		return make_pair(a.dwCursorPosition.X, a.dwCursorPosition.Y);
	};

};
CoordinateSystem& createCuusor();
CoordinateSystem& createPoint();
