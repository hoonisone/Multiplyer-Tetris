#pragma once
#include <string>
#include "ColorPrinter.h"
#include "Object.h"
#include "Painter.h"
using namespace std;
class Scanner : Object{
private:
	int width, height;
	string content;
	Printer* printer;
public:
	Scanner(int width, int height, Printer* printer): width(width), height(height), printer(printer) {};
	void draw(int drawX, int drawY) override{
		Object::setDrawPosition(drawX, drawY);
		redraw();
	}
	void redraw() override {
		printer->printText(drawX, drawY, width, height, { content });
	}
	void enter(char c) {
		if(content.size() < width) // 버퍼가 차지 않았다면.
			content.push_back(c);
	}
	void backspace() {	// backspcae
		if (!content.empty())
			content.pop_back();
	}
	void erase() {
		Painter({ " " }).rect(drawX, drawY, width, height);
	}
	void empty() {
		content = "";
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
	string getContent() {
		return content;
	}
};