#pragma once
#include <vector>
#include <string>
#include "Consol.h"
#include "CoordinateSystem.h"

enum AlignX { LEFT, CENTER, RIGHT };
enum AlignY { TOP, MIDDLE, BOTTOM };

class Printer{
private:
	static void printText(int x, int y, string text) {
		CURSOR.move(x, y);
		cout << text;
	}
	static int getPrintPosX(int x, int w, int len, AlignX align) {
		switch (align) {
		case LEFT:
			return x;
		case CENTER:
			return x + (w - len) / 2;
		case RIGHT:
			return x + (w - len);
		}
	}
	static int getPrintPosY(int y, int h, int n, AlignY align) {
		return getPrintPosX(y, h, n, (AlignX)align);
	}
public:
	static void printText(int x, int y, int w, int h, string text,
		Color textColor = WHITE, Color backgroundColor = BLACK, AlignX alignX = LEFT, AlignY alignY = MIDDLE) {
		vector<string> tokens = { text };
		printText(x, y, w, h, tokens, textColor, backgroundColor, alignX, alignY);
	}

	static void printText(int x, int y, int w, int h, vector<string> tokens,
		Color textColor = WHITE, Color backgroundColor = BLACK, AlignX alignX = LEFT, AlignY alignY = MIDDLE) {
		Consol::changeTextColor(textColor);
		
		Consol::changeBackgroundColor(backgroundColor);
		int Y = getPrintPosY(y, h, tokens.size(), alignY);
		
		int X;
		for (int i = 0; i < tokens.size(); i++) {
			X = getPrintPosX(x, w, tokens[i].size(), alignX);
			printText(X, Y + i, tokens[i]);
		}
	}
};