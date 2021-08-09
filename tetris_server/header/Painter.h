#pragma once
#include "CoordinateSystem.h"
#include "Pencil.h"

/*
�ܼ�â�� ���ϴ� �������� �ٶ󺸰� �׸��� �׸� �� �ִ�.
��ǥ��(CoordinateSystem)�� �ܼ�â�� x, y���� ���ϴ� ��ŭ Ȯ�� ��� ���ش�.
��(Pencil)�� ������ ��, ����, �� ����� �����Ѵ�.

�ѹ� �����ϸ� Ư���� ��ǥ�� ��, ������� �׸��� �׸� �� �ִ�.
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