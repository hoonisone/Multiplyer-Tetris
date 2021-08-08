#include <iostream>
#include "Printer.h"

void Printer::printText(int x, int y, string text) {
	CURSOR.move(x, y);
	pencil.press();		// »ö »õÆÃ
	cout << text;
}