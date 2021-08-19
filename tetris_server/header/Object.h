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
	virtual void draw(int x, int y) = 0;
	virtual void draw() = 0;
	virtual void update(string data) {}
	virtual void update(char data) {}
	virtual void update() {}
	virtual void erase() = 0;
	int getWidth() {
		return w;
	}
	int getHeight() {
		return h;
	}
};