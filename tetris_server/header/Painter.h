#pragma once
#include "CoordinateSystem.h"
#include "Pencil.h"

/*
콘솔창을 원하는 관점에서 바라보고 그림을 그릴 수 있다.
좌표계(CoordinateSystem)는 콘솔창의 x, y축을 원하는 만큼 확대 축소 해준다.
펜(Pencil)은 도형의 색, 배경색, 점 모양을 설정한다.

한번 생성하면 특정한 좌표와 색, 모양으로 그림을 그릴 수 있다.
*/

class Painter {
private:
	CoordinateSystem coordinateSystem;
	Pencil pencil;
public:
	Painter() : coordinateSystem(CURSOR), pencil(Pencil({ "*" }, WHITE, BLACK)) {}
	Painter(Pencil p) : coordinateSystem(CURSOR), pencil(p) {}
	Painter(CoordinateSystem cs, Pencil p) : coordinateSystem(cs), pencil(p) {}
	void point(int x, int y) {
		coordinateSystem.move(x, y);
		pencil.press();
	}
	void horizontal(int x, int y, int w) {
		for (int i = 0; i < w; i++) {
			point(x + i, y);
		}
	}
	void vertical(int x, int y, int h) {
		for (int i = 0; i < h; i++) {
			point(x, y + i);
		}
	}
	void rect(int x, int y, int w, int h) {
		horizontal(x, y, w);
		vertical(x, y, h);
		horizontal(x, y + h - 1, w);
		vertical(x + w - 1, y, h);
	}
};