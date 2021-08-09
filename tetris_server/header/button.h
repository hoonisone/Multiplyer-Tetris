#pragma once
#include <string>
#include "Consol.h"
#include "Printer.h"
#include "ButtonAction.h"
#include "Painter.h"
#include "string+.h"

class Button {
private:
	int x, y, w, h;
	string text;
	AlignX alignX;
	AlignY alignY;
	bool borderFlag;
	Color textColor, textBackgroundColor;
	Color borderColor, borderBackgroundColor;
	ButtonAction *buttonAction;

public:
	Button(int x, int y, int w, int h, string text = "",
		Color textColor = WHITE, Color backgroundColor = BLACK, 
		bool borderFlag = true, Color borderColor = WHITE, Color borderBackgroundColor = BLACK,
		AlignX alignX = CENTER, AlignY alignY = MIDDLE,
		ButtonAction *buttonAction = new DefaultButtonAction()) {
		setPos(x, y);
		setSize(w, h);
		setText(text);
		setAlign(alignX, alignY);
		setBorder(borderFlag, borderColor, borderBackgroundColor);
		setTextColor(textColor, backgroundColor);
		setAction(buttonAction);
	};
	void setPos(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void setSize(int w, int h) {
		this->w = w;
		this->h = h;
	}
	void setText(string text) {
		this->text = text;
	}
	void setAlign(AlignX alignX, AlignY alignY) {
		this->alignX = alignX;
		this->alignY = alignY;
	}
	void setBorder(bool borderFlag, Color borderColor = WHITE, Color borderBackgroundColor = BLACK) {
		this->borderFlag = borderFlag;
		this->borderColor = borderColor;
		this->borderBackgroundColor = borderBackgroundColor;
	}
	void setTextColor(Color textColor = WHITE, Color backgroundColor = BLACK) {
		this->textColor = textColor;
		this->textBackgroundColor = backgroundColor;
		this->borderColor = borderColor;
	}
	void setAction(ButtonAction *buttonAction) {
		this->buttonAction = buttonAction;
	}
	void draw() {
		if (borderFlag) {
			Painter painter = Painter(Pencil({ "*" }, borderColor, borderBackgroundColor));
			painter.rect(x, y, w, h);
		}
		vector<string>tokens = split(text, "\n");
		Printer::printText(x + 1, y + 1, w - 2, h - 2, tokens, textColor, textBackgroundColor, alignX, alignY);
	}
};