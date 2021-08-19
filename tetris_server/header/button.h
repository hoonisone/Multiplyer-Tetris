#pragma once
#include <string>
#include "Consol.h"
#include "Printer.h"
#include "Painter.h"
#include "ColorPrinter.h"
#include "ColorPainter.h"
#include "ButtonAction.h"
#include "string+.h"
#include "system.h"
#include "Object.h"

class Button : public Object{
protected:
	string text;
	bool borderFlag;
	bool selectFlag;
	string (*action)(Button* button) = NULL;
	Printer* unselectPrinter = NULL, * selectPrinter = NULL;
	Painter* unselectPainter = NULL, * selectPainter = NULL;
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
public:
	Button(int x, int y, int w, int h, string text,
		Painter* unselectPainter, Printer* unselectPrinter, Painter* selectPainter, Printer* selectPrinter, bool borderFlag = true) : Object(x, y, w, h), selectFlag(false) {
		setText(text);
		setUnselectPrinter(unselectPrinter);
		setUnselectPainter(unselectPainter);
		setSelectPrinter(selectPrinter);
		setSelectPainter(selectPainter);
		setBorderFlag(borderFlag);
		this->selectFlag = selectFlag;
	};
	void draw(int x, int y) override{
		Object::setDrawPosition(x, y);
		draw();
	}
	void draw() override {
		erase();
		if (borderFlag) {
			if (selectFlag) {
				selectPainter->rectBorder(x, y, w, h, CURSOR_STD);
			}
			else {
				unselectPainter->rectBorder(x, y, w, h, CURSOR_STD);
			}
		}
		vector<string>tokens = split(text, "\n");
		if (selectFlag) {
			selectPrinter->printText(x + unselectPainter->getWidth(), y + unselectPainter->getHeight(), w - 2 * unselectPainter->getWidth(), h - 2 * unselectPainter->getHeight(), tokens);
		}
		else {
			unselectPrinter->printText(x + unselectPainter->getWidth(), y + unselectPainter->getHeight(), w - 2 * unselectPainter->getWidth(), h - 2 * unselectPainter->getHeight(), tokens);
		}
	}
	void erase() override {
		Painter({ " " }).rect(x, y, w * selectPainter->getWidth(), h * selectPainter->getHeight());
	}
	void select() {
		this->selectFlag = true;
	}
	void unselect() {
		this->selectFlag = false;
	}
	string click() {
		if (action != NULL) { 
			return action(this); 
		}
	}
	virtual void update(char key) {
		return;
	}
	virtual string getText() {
		return text;
	}

	~Button() {
		if (unselectPainter != NULL) FREE(unselectPainter);
		if (unselectPrinter != NULL) FREE(unselectPrinter);
		if (selectPainter != NULL) FREE(selectPainter);
		if (selectPrinter != NULL) FREE(selectPrinter);
	}
};