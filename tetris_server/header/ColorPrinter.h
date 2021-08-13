#pragma once
#include "Printer.h"

class ColorPrinter : public Printer{
private:
	Color textColor, backgroundColor;
	void setting(Color textColor, Color backgroundColor) const {
		Consol::changeTextColor(textColor);
		Consol::changeBackgroundColor(backgroundColor);
	}
public:
	ColorPrinter(const ColorPrinter& object) : ColorPrinter(object.alignX, object.alignY, object.textColor, object.backgroundColor) {};
	ColorPrinter(const ColorPrinter * object) : ColorPrinter(*object) {};
	ColorPrinter(AlignX alignX = LEFT, AlignY alignY = MIDDLE, Color textColor = WHITE, Color backgroundColor = BLACK) :Printer(alignX, alignY),
		textColor(textColor), backgroundColor(backgroundColor){
	}
	virtual Printer* newObject() const{
		return new ColorPrinter(this);
	}
	void setColor(Color textColor, Color backgroundColor) {
		this->textColor = textColor;
		this->backgroundColor = backgroundColor;
	}
	virtual void printText(int x, int y, int w, int h, vector<string> tokens) const {
		setting(textColor, backgroundColor);
		Printer::printText(x, y, w, h, tokens);
	}
};