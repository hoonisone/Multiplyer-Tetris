#pragma once
#include <string>
#include "ColorPrinter.h"
#include "Object.h"

using namespace std;
class Scanner : Object{
private:
	int drawX, drawY;
	int width, height;
	string content;
	Printer* printer;
public:
	Scanner(int width, int height, Printer* printer): width(width), height(height), printer(printer) {};
	void draw(int drawX, int drawY) override{
		setDrawPosition(drawX, drawY);
		redraw();
	}
	void redraw() override {
		printer->printText(drawX, drawY, width, height, { content });
	}
	void enter(char c) {
		content.push_back(c);
	}
	void enter(string s) {
		content += s;
	}
	void empty() {
		content = "";
	}
	string getContent() {
		return content;
	}
};