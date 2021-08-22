#pragma once
#include "Scanner.h"

class ScannerCreator {
public:
	Scanner* createScanner(int x, int y, int w, int h, Printer* printer) {
		return new Scanner(x, y, w, h, printer);
	};
};