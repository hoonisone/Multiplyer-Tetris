#pragma once
#include <string>
#include "Consol.h"
#include "Printer.h"
#include "ButtonAction.h"
#include "string+.h"

class Button {
private:


public:
	int x, y, w, h;
	string text;
	Printer unclickPrinter, clickPrinter;
	Painter unclickPainter, clickPainter;
	bool borderFlag;
	ButtonAction* buttonAction;
	bool clickFlag;
	Button(int x, int y, int w, int h, string text, Painter unclickPainter, Printer unclickPprinter, Painter clickPainter, Printer clickPrinter,
		bool borderFlag = true, ButtonAction* buttonAction = new DefaultButtonAction()) : clickFlag(false) {
		setPos(x, y);
		setSize(w, h);
		setText(text);
		setUnclickPrinter(unclickPrinter);
		setUnclickPainter(unclickPainter);
		setClickPrinter(clickPrinter);
		setClickPainter(clickPainter);
		setBorderFlag(borderFlag);
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
	void setUnclickPrinter(Printer printer) {
		this->unclickPrinter = printer;
	}
	void setUnclickPainter(Painter painter) {
		this->unclickPainter = painter;
	}
	void setClickPrinter(Printer printer) {
		this->unclickPrinter = printer;
	}
	void setClickPainter(Painter painter) {
		this->unclickPainter = painter;
	}
	void setBorderFlag(bool borderFlag) {
		this->borderFlag = borderFlag;
	}
	void setAction(ButtonAction *buttonAction) {
		this->buttonAction = buttonAction;
	}
	void draw() {
		if (borderFlag) {
			if (clickFlag) {
				clickPainter.rect(x, y, w, h);
			}
			else {
				unclickPainter.rect(x, y, w, h);
			}
		}
		vector<string>tokens = split(text, "\n");
		if (clickFlag) {
			clickPrinter.printText(x + unclickPainter.pw, y + unclickPainter.ph, w - 2 * unclickPainter.pw, h - 2 * unclickPainter.ph, tokens);
		}
		else {
			unclickPrinter.printText(x + unclickPainter.pw, y + unclickPainter.ph, (w - 2) * unclickPainter.pw, (h - 2) * unclickPainter.ph, tokens);
		}
	}
	void click() {
		this->clickFlag = true;
	}
	void unclick() {
		this->clickFlag = false;
	}
};