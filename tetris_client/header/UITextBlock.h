//#pragma once
//#include <string>
//#include "Consol.h"
//#include "Printer.h"
//#include "Painter.h"
//#include "ColorPrinter.h"
//#include "ColorPainter.h"
//#include "string+.h"
//#include "system.h"
//#include "UIElement.h"
//
//class UITextBlock : public UIElement{
//private:
//	string text;
//	bool borderFlag;
//	Printer* unselectedPrinter = NULL, * selectedPrinter = NULL, * printer = NULL;
//	Painter* unselectedPainter = NULL, * selectedPainter = NULL, * painter = NULL;
//	void drawBorder() {
//		if (borderFlag)	painter->rectBorder(x, y, w, h, CURSOR_STD);
//	}
//	void drawText() {
//		vector<string>tokens = split(text, "\n");
//		printer->printText(x + painter->getWidth(), y + painter->getHeight(), w - 2 * painter->getWidth(), h - 2 * painter->getHeight(), tokens);
//	}
//public:
//	UITextBlock(int x, int y, int w, int h, string text, Painter* unselectedPainter, Printer* unselectedPrinter, 
//		Painter* selectedPainter, Printer* selectedPrinter, bool borderFlag = true) : 
//		UIElement(x, y, w, h), text(text), unselectedPainter(unselectedPainter), unselectedPrinter(unselectedPrinter),
//		selectedPainter(selectedPainter), selectedPrinter(selectedPrinter), borderFlag(borderFlag){
//		unselect();	// unselecte 상태로 초기화
//	};
//	virtual void select(bool redraw = true) override {
//		selectFlag = true;
//		printer = selectedPrinter;
//		painter = selectedPainter;
//	}
//	virtual void unselect(bool redraw = true) override{
//		selectFlag = false;
//		printer = unselectedPrinter;
//		painter = unselectedPainter;
//	}
//	virtual void draw() override  {
//		drawBorder();
//		drawText();
//	}
//	virtual string getText() {
//		return text;
//	}
//	~UITextBlock() {
//		if (unselectedPainter != NULL) FREE(unselectedPainter);
//		if (unselectedPrinter != NULL) FREE(unselectedPrinter);
//		if (selectedPainter != NULL) FREE(selectedPainter);
//		if (selectedPrinter != NULL) FREE(selectedPrinter);
//	}
//};