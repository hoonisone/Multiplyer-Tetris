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
		if (c == 8) {	// backspace�� ��� �� �� ���� ����
			if (!text.empty()) {
				if(redraw) erase();	// ���� ���� �پ��� �� �� ���ڰ� �������� �� �����Ƿ� ���� ����ϰ� ������
				text.pop_back();
				if (redraw) draw();
			}
		}
		else {
			if (text.size() < w) { // ���۰� ���� �ʾҴٸ�.
				text.push_back(c);	// �Էµ� ���� �߰�
				if (redraw) draw();	// ���ڰ� �߰��� ���̱� ������ ����� �ؽ�Ʈ�� �״�� ����� �ȴ�.
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