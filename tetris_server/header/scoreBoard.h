#pragma once
#include "ColorPainter.h"
#include "ColorPrinter.h"
typedef struct ScoreBoard {
	int drawX=0, drawY=0;
	int width, height = 9;
	Painter* painter;
	Printer* keyPrinter;
	Printer* valuePrinter;
	Painter* eraser;
public:
	ScoreBoard(int width, ColorPainter* painter) : width(width), painter(painter) {
		keyPrinter = new ColorPrinter(LEFT);	// key는 좌측 정렬
		valuePrinter = new ColorPrinter(RIGHT);	// value는 우측 정렬
		eraser = new ColorPainter({" "});
	};
	virtual void drawPointSetting(int drawX, int drawY) {
		this->drawX = drawX;
		this->drawY = drawY;
	}
	virtual void draw(int drawX, int drawY, int level, int score, int line, int block) {
		drawPointSetting(drawX, drawY);
		redrawContent(level, score, line, block);
		redrawFrame();
	}
	virtual void drawContent(int drawX, int drawY, int level, int score, int line, int block) {
		drawPointSetting(drawX, drawY);
		redrawContent(level , score, line, block);
	}
	virtual void redrawContent(int level, int score, int line, int block) {
		vector<int> values = { level, score, line, block };
		for (int i = 0; i < values.size(); i++) {
			int x = drawX;
			int y = drawY + 2 * i;
			valuePrinter->printText(x + 2, y + 1, width - 4, 1, { to_string(values[i]) });
		}
	}
	virtual void erase() {
		eraser->rect(drawX, drawY, width, height);
	}
	virtual void drawFrame(int drawX, int drawY) {
		drawPointSetting(drawX, drawY);
		redrawFrame();
	}
	virtual void redrawFrame() {
		static vector<string> keys = { "Level", "Score", "Line ", "Block" };
		for (int i = 0; i < keys.size(); i++) {
			int x = drawX;
			int y = drawY + 2 * i;
			painter->rectBorder(x, y, width, 3, CURSOR_STD);
			keyPrinter->printText(x + 2, y + 1, width * 2 - 4, 1, { keys[i] });
		}
	}
	virtual int getWidth() {
		return width;
	}
	virtual int getHeight() {
		return height;
	}
	~ScoreBoard() {
		delete painter;
		delete keyPrinter;
		delete valuePrinter;
		delete eraser;
	}
};
