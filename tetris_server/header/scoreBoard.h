#pragma once
#include "ColorPainter.h"
#include "ColorPrinter.h"
typedef struct ScoreBoard {
	int width;
	int height = 3;
public:
	ScoreBoard(int width): width(width) {};
	virtual void draw(int drawX, int drawY, int level, int score, int line, int block) {
		Painter painter({ "¡¤" });
		Printer keyPrinter(LEFT);
		Printer valuePrinter(RIGHT);
		vector<int> values = { level, score, line, block };
		vector<string> keys = { "Level", "Score", "Line ", "Block" };

		for (int i = 0; i < values.size(); i++) {
			int x = drawX;
			int y = drawY + (height - 1) * i;
			painter.rectBorder(x, y, width/painter.getWidth(), height / painter.getHeight());
			Consol::move(x+2, y+1);
			keyPrinter.printText(x + 2, y + 1, width*2-4, height - 2, { keys[i] });
			valuePrinter.printText(x + 2, y + 1, width -4, height - 2, { to_string(values[i]) });
		}
	}
	virtual int getWidth() {
		return width;
	}
	virtual int getHeight() {
		return height;
	}
};
