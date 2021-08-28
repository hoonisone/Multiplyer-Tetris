#pragma once
#include "Scanner.h"
#include "ScannerCreator.h"
#include "UIElement.h"
#include "error.h"

class UIScannerElement : public UIElement{
protected:
	Scanner* scanner;
	void drawBorder() {
		painter->rectBorder(x, y, w, h, CURSOR_STD);
	}
	void drawScanner() {
		scanner->draw();
	}
public:
	UIScannerElement(int x, int y, int w, int h, string name, ScannerCreator* scannerCreator) :UIScannerElement(x, y, w, h, name, scannerCreator, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true) {};
	UIScannerElement(int x, int y, int w, int h, string name, ScannerCreator * scannerCreator, Painter* selectedPainter, Painter* unselectedPainter,
		Printer* selectedPrinter, Printer* unselectedPrinter, const bool borderFlag = true):
		UIElement(x, y, w, h, name, selectedPainter, unselectedPainter, selectedPrinter, unselectedPrinter, borderFlag, 0, 0){
		if(!unselectedPainter->checkPointSize(selectedPainter))	// 두 Painter의 point shape가 동일해야 한다.
			errorPrint("selectedPainter's piont shape is not same to unselectedPainter's");
		int pw = unselectedPainter->getWidth();
		int ph = unselectedPainter->getHeight();
		this->scanner = scannerCreator->createScanner(x + pw, y + ph, w - 2 * pw, h - 2 * ph, new Printer(CENTER, MIDDLE));	// Element 크기에 테두리를 제외한 내부크기에 맞게 Scanner생성
		delete scannerCreator;
		unselect(false);
	}
	void draw() {
		drawBorder();
		drawScanner();
		// Scanner는 자식이 없으므로 자식을 그리지 않는다.
	}
	void move(int dx, int dy, bool redraw = true) override{
		UIElement::move(dx, dy);
		scanner->move(dx, dy);
	}
	State getState() {
		return {make_pair(name, scanner->getText())};
	}

	bool  keyInputHandler(char key) override{
		switch (key) {
		case KEY_UP:
		case KEY_DOWN:
		case KEY_LEFT:
		case KEY_RIGHT:
			return false;	// 방향키는 실패 처리하여 부모에게 점긴다.
		default: scanner->enter(key); break;	// 방향키 이외의 입력은 scanner에게 넘긴다.
		}
	}
};