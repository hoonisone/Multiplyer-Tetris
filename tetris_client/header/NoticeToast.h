#pragma once

#include "Toast.h"
#include "string+.h"
#include "Printer.h"
#include <vector>
#include <string>
#include "KeyInput.h"
#include "ColorPainter.h"
#include "ColorPrinter.h"
class NoticeToast: public Toast {
public:
	string action(string notice) override{
		vector<string> lines = split(notice, "\n");
		lines.push_back("");
		lines.push_back("Press Enter!!");
		int h = lines.size()+2+2;	// 테두리 고려 1*2    여백 1*2
		int w = 0;
		for (string line : lines) {
			if (w < line.size())
				w = line.size();
		}
		w += 2+8;	// 테두리 고려 1*2    여백 4*2
		int x = (WIDTH - w) / 2;
		int y = (HEIGHT - h) / 2;
		ColorPainter::GetEraser(w, h).point(x, y);
		ColorPainter({ "#" }).rectBorder(x, y, w, h, CURSOR_STD);
		ColorPrinter(CENTER, MIDDLE).printText(x + 1, y + 1, w - 2, h - 2, lines);
		while (Input::getKey() != KEY_ENTER);	// enter를 입력하면 종료
		return "";
	}
};