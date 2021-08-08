#include "Pencil.h"
#include "Consol.h"

Pencil::Pencil(Color textColor, Color backgroundColor, Shape textShape) :
	textColor(textColor), backgroundColor(backgroundColor), textShape(textShape) {};
void Pencil::press() {
	setting();
	pair<int, int> curPosition = CoordinateSystem::getCoordinate();
	int X = curPosition.first;
	int Y = curPosition.second;
	for (int i = 0; i < textShape.size(); i++) {
		CURSOR.move(X, Y + i);
		cout << textShape[i];
	}
}
void Pencil::setting() {
	if (usingPencil == nullptr || usingPencil != this) {
		usingPencil = this;
		// set text color
		Consol::changeTextColor(textColor);
		// set background color
		Consol::changeBackgroundColor(backgroundColor);
	}
}