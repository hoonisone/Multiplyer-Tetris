#pragma once
#include "Scanner.h"
#include "ScannerCreator.h"
#include "UIElement.h"
#include "error.h"
#include "UIManager.h"

class UIScannerBlock : public UIElement{
private:
	Scanner* scanner;
	void drawBorder() {
		painter->rectBorder(x, y, w, h);
	}
	void drawScanner() {
		scanner->draw();
	}
public:
	UIScannerBlock(int x, int y, int w, int h, ScannerCreator* scannerCreator) :UIScannerBlock(x, y, w, h, scannerCreator, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true) {};
	UIScannerBlock(int x, int y, int w, int h, ScannerCreator * scannerCreator, Painter* selectedPainter, Painter* unselectedPainter,
		Printer* selectedPrinter, Printer* unselectedPrinter, const bool borderFlag = true):
		UIElement(x, y, w, h, "", selectedPainter, unselectedPainter, selectedPrinter, unselectedPrinter, borderFlag, 0, 0){
		if(!unselectedPainter->checkPointSize(selectedPainter))	// �� Painter�� point shape�� �����ؾ� �Ѵ�.
			errorPrint("selectedPainter's piont shape is not same to unselectedPainter's");
		int pw = unselectedPainter->getWidth();
		int ph = unselectedPainter->getHeight();
		this->scanner = scannerCreator->createScanner(x+pw, y+ph, w-2*pw, h-2*ph, new Printer());
		delete scannerCreator;
		unselect();
	}

	void draw() {
		drawBorder();
		drawScanner();
		// Scanner�� �ڽ��� ������ ��찡 �����Ƿ� ��� �ڵ� ��� ��
	}
	string getText() {
		return scanner->getText();
	}
	void keyInputHandler(char key) override{
		switch (key) {
		case KEY_UP:    selectUpChild();    break;
		case KEY_DOWN:  selectDownChild();  break;
		case KEY_LEFT:  selectLeftChild();  break;
		case KEY_RIGHT: selectRightChild(); break;
		default: scanner->enter(key); break;	// ����Ű �̿��� �Է��� scanner���� �ѱ��.
		}
	}
};