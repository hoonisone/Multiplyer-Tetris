#pragma once
#include <string>
#include "ColorPrinter.h"
#include "UIElement.h"
#include "Painter.h"
using namespace std;
class Scanner{
private:
	int x, y, w, h;
	string text;
	Printer* printer;
	bool checkInputRange(char c) {
		return (21 <= c && c <= 126) || c==8;
	}
public:
	void move(int dx, int dy, bool redraw = true) {
		if (redraw) erase();
		x += dx;
		y += dy;
		if (redraw) draw();
	}
	Scanner(int x, int y, int w, int h, Printer* printer): x(x), y(y), w(w), h(h), printer(printer) {};
	void draw() {
		printer->printText(x, y, w, h, { text });
	}
	void erase() {
		Painter({ " " }).rect(x, y, w, h);
	}
	void enter(char c, bool redraw = true) {
		if (!checkInputRange(c))
			return;
		if (c == 8) {	// backspace인 경우 맨 뒷 글자 제거
			if (!text.empty()) {
				if(redraw) erase();	// 글자 수가 줄어들면 이 전 글자가 남아있을 수 있으므로 먼저 깔끔하게 지워줌
				text.pop_back();
				if (redraw) draw();
			}
		}
		else {
			if (text.size() < w) { // 버퍼가 차지 않았다면.
				text.push_back(c);	// 입력된 글자 추가
				if (redraw) draw();	// 글자가 추가된 것이기 때문에 길어진 텍스트를 그대로 덮어쓰면 된다.
			}
		}
	}
	void emptyOut(bool redraw = true) {
		if (redraw) erase();
		text = "";
	}
	string getText() {
		return text;
	}
	~Scanner() {
		delete printer;
	}
};