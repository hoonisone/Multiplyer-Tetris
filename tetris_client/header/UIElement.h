#pragma once
#include <string>
#include "Consol.h"
#include "Printer.h"
#include "Painter.h"
#include "ColorPrinter.h"
#include "ColorPainter.h"
#include "string+.h"
#include "system.h"
#include "Object.h"

class UIElement : public ConsolObject{
protected:
	string text;
	bool borderFlag;
	bool selectFlag;
	string (*action)(UIElement* button) = NULL;	// 버튼 클릭시 수행 될 함수
	Printer* unselectedPrinter = NULL, * selectedPrinter = NULL, * printer = NULL;
	Painter* unselectedPainter = NULL, * selectedPainter = NULL, * painter = NULL;
	void setAction(void (*_action)(UIElement* element)) {
		this->action = action;
	}
	void drawBorder() {
		if (borderFlag)	painter->rectBorder(x, y, w, h, CURSOR_STD);
	}
	void drawText() {
		vector<string>tokens = split(text, "\n");
		printer->printText(x + painter->getWidth(), y + painter->getHeight(), w - 2 * painter->getWidth(), h - 2 * painter->getHeight(), tokens);
	}
public:
	UIElement(int x, int y, int w, int h, string text, Painter* unselectedPainter, Printer* unselectedPrinter, 
		Painter* selectedPainter, Printer* selectedPrinter, bool borderFlag = true) : 
		ConsolObject(x, y, w, h), text(text), unselectedPainter(unselectedPainter), unselectedPrinter(unselectedPrinter),
		selectedPainter(selectedPainter), selectedPrinter(selectedPrinter), borderFlag(borderFlag){
		unselect();	// unselecte 상태로 초기화
	};
	void move(int x, int y, bool redraw = true) override{
		if (redraw)erase();
		ConsolObject::move(x, y);
		if(redraw)draw();
	}
	void draw() override  {
		drawBorder();
		drawText();
	}
	void erase() override {
		Painter({ " " }).rect(x, y, w * selectedPainter->getWidth(), h * selectedPainter->getHeight());
	}
	void select(bool redraw = true) {
		selectFlag = true;
		if (redraw) erase();
		printer = selectedPrinter;
		painter = selectedPainter;
		if (redraw) draw();
	}
	void unselect(bool redraw = true) {
		selectFlag = false;
		if (redraw) erase();
		printer = unselectedPrinter;
		painter = unselectedPainter;
		if (redraw) draw();
	}
	string click() {
		if (action != NULL) { 
			return action(this); 
		}
	}
	virtual void update(char key, bool redraw = true) {
		if (redraw) erase();
		// 수정 내용
		if (redraw) draw();
	}
	virtual string getText() {
		return text;
	}

	~UIElement() {
		if (unselectedPainter != NULL) FREE(unselectedPainter);
		if (unselectedPrinter != NULL) FREE(unselectedPrinter);
		if (selectedPainter != NULL) FREE(selectedPainter);
		if (selectedPrinter != NULL) FREE(selectedPrinter);
	}
};