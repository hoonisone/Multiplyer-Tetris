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
	virtual void draw(const int x, const int y) = 0;	// 객체의 위치를 변경함과 동시에 출력한다.
	virtual void draw()  = 0;	// 기존 위치에 객체를 그린다.
	virtual void update(string data, bool redraw=true) {} // 입력에 대해 객체를 갱신한다.
	virtual void update(char data, bool redraw = true) {} // 입력에 대해 객체를 갱신한다.
	virtual void update(bool redraw = true) {} // 입력에 대해 객체를 갱신한다.
	virtual void erase() = 0;	// 기존 위치에 객체를 지운다.
	int getWidth() {
		return w;
	}
	int getHeight() {
		return h;
	}
};