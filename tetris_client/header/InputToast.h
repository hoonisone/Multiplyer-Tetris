#pragma once

#include "Toast.h"
#include <vector>
#include <string>
#include "string+.h"
#include "ColorPainter.h"
#include "ColorPrinter.h"
#include "KeyInput.h"
#include "Scanner.h"
class InputToast : public Toast {
public:
	string action(vector<string> lines) {
		lines.push_back("");
		lines.push_back("");	// 여백
		int h = lines.size() + 2 + 2;	// 테두리 고려 1*2    여백 1*2
		int w = 0;
		for (string line : lines) {
			if (w < line.size())
				w = line.size();
		}
		w += 2 + 8;	// 테두리 고려 1*2    여백 4*2
		w = max(30, w);
		int x = (WIDTH - w) / 2;
		int y = (HEIGHT - h) / 2;
		ColorPainter::GetEraser(w, h).point(x, y);
		ColorPainter({ "#" }).rectBorder(x, y, w, h, CURSOR_STD);
		ColorPrinter(CENTER, MIDDLE).printText(x + 1, y + 1, w - 2, h - 2, lines);
		int sW = w - 10;
		int sH = 1;
		int sX = WIDTH / 2 - sW / 2;
		int sY = y + h - 3;
		Scanner scanner = Scanner(sX, sY, sW, sH, new Printer(CENTER, MIDDLE));

		bool whileFlag = true;
		while (whileFlag) {
			char c = (char)Input::getKey();
			switch (c) {
			case KEY_ENTER:
				whileFlag = false;
				break;
			default:
				scanner.enter(c);
			}
		}
		ColorPainter::GetEraser(w, h).point(x, y);
		return scanner.getText();
	}
	string action(string question)override {
		vector<string> lines = split(question, "\n");
		return action(lines);
	}
};