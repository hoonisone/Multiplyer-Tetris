#include "Pencil.h"

Pencil::Pencil(Color textColor, Color backgroundColor, Shape textShape) :
	textColor(textColor), backgroundColor(backgroundColor), textShape(textShape) {};
void Pencil::press() {
	if (usingPencil == nullptr || usingPencil != this) {
		usingPencil = this;
		setting();
	}
	pair<int, int> curPosition = CoordinateSystem::getCoordinate();
	int X = curPosition.first;
	int Y = curPosition.second;
	for (int i = 0; i < textShape.size(); i++) {
		CURSOR.move(X, Y + i);
		cout << textShape[i];
	}
}
void Pencil::setting() {
	// set text color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
	// set background color
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((backgroundColor & 0xf) << 4) | (info.wAttributes & 0xf));
}