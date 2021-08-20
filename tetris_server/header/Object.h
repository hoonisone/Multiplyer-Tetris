#pragma once

class Object {
protected:

public:
	int x, y;
	int w, h;
	Object(int x, int y, int w, int h) :x(x), y(y), w(w), h(h){};
	virtual void setDrawPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}
	virtual void draw(const int x, const int y) = 0;	// ��ü�� ��ġ�� �����԰� ���ÿ� ����Ѵ�.
	virtual void draw()  = 0;	// ���� ��ġ�� ��ü�� �׸���.
	virtual void update(string data, bool redraw=true) {} // �Է¿� ���� ��ü�� �����Ѵ�.
	virtual void update(char data, bool redraw = true) {} // �Է¿� ���� ��ü�� �����Ѵ�.
	virtual void update(bool redraw = true) {} // �Է¿� ���� ��ü�� �����Ѵ�.
	virtual void erase() = 0;	// ���� ��ġ�� ��ü�� �����.
	int getWidth() {
		return w;
	}
	int getHeight() {
		return h;
	}
};