#include <iostream>
#include "Printer.h"
#include "Consol.h"

void Printer::printText(int x, int y, string text, Color textColor, Color backgroundColor) {
	Consol::changeTextColor(textColor);
	Consol::changeBackgroundColor(backgroundColor);
	CURSOR.move(x, y);
	cout << text;
}