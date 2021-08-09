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
	Painter();
	Painter(Pencil p);
	Painter(CoordinateSystem cs, Pencil p);
	void point(int x, int y);
	void horizontal(int x, int y, int width);
	void vertical(int x, int y, int height);
	void rect(int x, int y, int width, int height);
};