#include "Painter.h"
Painter::Painter() : coordinateSystem(CURSOR), pencil(Pencil(WHITE, BLACK, { "*" })) {}
Painter::Painter(Pencil p) : coordinateSystem(CURSOR), pencil(p) {}
Painter::Painter(CoordinateSystem cs, Pencil p) : coordinateSystem(cs), pencil(p) {}
void Painter::point(int x, int y) {
	coordinateSystem.move(x, y);
	pencil.press();
}
void Painter::horizontal(int x, int y, int width) {
	for (int i = 0; i < width; i++) {
		point(x + i, y);
	}
}
void Painter::vertical(int x, int y, int height) {
	for (int i = 0; i < height; i++) {
		point(x, y+i);
	}
}
void Painter::rect(int x, int y, int width, int height) {
	horizontal(x, y, width);
	vertical(x, y, height);
	horizontal(x, y + height - 1, width);
	vertical(x + width - 1, y, height);
}