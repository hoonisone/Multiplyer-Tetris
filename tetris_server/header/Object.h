#pragma once

class Object {
private:
	int drawX, drawY;
public:
	virtual void setDrawPosition(int drawX, int drawY) {
		this->drawX = drawX;
		this->drawY = drawY;
	}
	virtual void draw(int drawX, int drawY) = 0;
	virtual void redraw() = 0;
};