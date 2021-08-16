#pragma once
#include "Scanner.h"
#include "Button.h"

class ScannerButton : Button{
private:
	Scanner* scanner;
	void drawButton() {
		Button::draw();

	}
	void drawScanner() {
		scanner->draw(x + selectPainter->getWidth(), y + selectPainter->getHeight());
	}
public:
	ScannerButton(int x, int y, Scanner* scanner, Painter* unselectPainter, Printer* unselectPrinter, Painter* selectPainter, Printer* selectPrinter, const bool borderFlag = true):
		Button(x, y, scanner->getWidth()+2*selectPainter->getWidth(), scanner->getHeight()+2*selectPainter->getHeight(), "", unselectPainter, unselectPrinter, selectPainter, selectPrinter, true) {
		this->scanner = scanner;
	}
	void draw() {
		drawButton();
		drawScanner();
	}
	void enter(char c){
		scanner->enter(c);
		drawScanner();
	}
	void backspace() {
		scanner->erase();
		scanner->backspace();
		drawScanner();
	}

};