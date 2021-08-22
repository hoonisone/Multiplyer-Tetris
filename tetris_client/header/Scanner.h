#pragma once
#include <string>
#include "ColorPrinter.h"
#include "Object.h"
#include "Painter.h"
using namespace std;
class Scanner : public ConsolObject{
private:
	string text;
	Printer* printer;
public:
	Scanner(int x, int y, int w, int h, Printer* printer): ConsolObject(x, y, w, h), printer(printer) {};
	void move(int drawX, int drawY, bool redraw = true) override {
		ConsolObject::move(drawX, drawY);
		if(redraw)draw();
	}
	void draw() override {
		printer->printText(x, y, w, h, { text });
	}
	void erase() override {
		Painter({ " " }).rect(x, y, w, h);
	}
	void enter(char c, bool redraw) {
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
};