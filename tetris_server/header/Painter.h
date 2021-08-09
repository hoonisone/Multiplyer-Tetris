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
	Painter();
	Painter(Pencil p);
	Painter(CoordinateSystem cs, Pencil p);
	void point(int x, int y);
	void horizontal(int x, int y, int width);
	void vertical(int x, int y, int height);
	void rect(int x, int y, int width, int height);
};