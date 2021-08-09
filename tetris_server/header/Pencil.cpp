#include "Pencil.h"
#include "Consol.h"
Pencil::Pencil(Shape textShape, Color textColor, Color backgroundColor) :textShape(textShape), textColor(textColor), backgroundColor(backgroundColor) {};

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
		Consol::changeTextColor(textColor);
		Consol::changeBackgroundColor(backgroundColor);
	}
}