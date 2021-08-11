#pragma once
#include <string>
#include "Consol.h"
#include "Printer.h"
#include "ButtonAction.h"
#include "string+.h"
#include "system.h"

class Button {
private:

public:
	int x, y, w, h;
	string text;
	Printer* unselectPrinter = NULL, * selectPrinter = NULL;
	Painter* unselectPainter = NULL, * selectPainter = NULL;
	bool borderFlag;
	void (*action)(Button* button) = NULL;
	bool selectFlag;
	Button(const int x, const int y, const int w, const int h, const string& text,
		Painter* unselectPainter, Printer *unselectPrinter, Painter* selectPainter, Printer* selectPrinter,
		const bool borderFlag = true) : selectFlag(false) {
		setPos(x, y);
		setSize(w, h);
		setText(text);
		setUnselectPrinter(unselectPrinter);
		setUnselectPainter(unselectPainter);
		setSelectPrinter(selectPrinter);
		setSelectPainter(selectPainter);
		setBorderFlag(borderFlag);
		this->selectFlag = selectFlag;
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
	void setUnselectPrinter(Printer* printer) {
		if (unselectPrinter != NULL) delete unselectPrinter;
		this->unselectPrinter = printer;
	}
	void setUnselectPainter(Painter* painter) {
		if (unselectPainter != NULL) delete unselectPainter;
		this->unselectPainter = painter;
	}
	void setSelectPrinter(Printer* printer) {
		if (selectPrinter != NULL) delete selectPrinter;
		this->selectPrinter = printer;
	}
	void setSelectPainter(Painter* painter) {
		if (selectPainter != NULL) delete selectPainter;
		this->selectPainter = painter;
	}
	void setBorderFlag(bool borderFlag) {
		this->borderFlag = borderFlag;
	}
	void setAction(void (*_action)(Button* button)) {
		this->action = action;
	}
	void draw()const {
		erase();
		if (borderFlag) {
			if (selectFlag) {
				selectPainter->borderRect(x, y, w, h);
			}
			else {
				unselectPainter->borderRect(x, y, w, h);
			}
		}
		vector<string>tokens = split(text, "\n");
		if (selectFlag) {
			selectPrinter->printText(x + unselectPainter->getWidth(), y + unselectPainter->getHeight(), (w - 2) * unselectPainter->getWidth(), (h - 2) * unselectPainter->getHeight(), tokens);
		}
		else {
			unselectPrinter->printText(x + unselectPainter->getWidth(), y + unselectPainter->getHeight(), (w - 2) * unselectPainter->getWidth(), (h - 2) * unselectPainter->getHeight(), tokens);
		}
	}
	void erase() const{
		Painter({ " " }).rect(x, y, w * selectPainter->getWidth(), h * selectPainter->getHeight());
	}
	void select() {
		this->selectFlag = true;
	}
	void unselect() {
		this->selectFlag = false;
	}
	void click() {
		if (action != NULL) { action(this); }
		else { cout << "button(" << text << ") is clicked"; }
	}
	~Button() {
		if (unselectPainter != NULL) FREE(unselectPainter);
		if (unselectPrinter != NULL) FREE(unselectPrinter);
		if (selectPainter != NULL) FREE(selectPainter);
		if (selectPrinter != NULL) FREE(selectPrinter);
	}
};