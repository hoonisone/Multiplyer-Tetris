#include "draw.h"

void Draw::horizontal(int x, int y, int width) {
	for (int i = 0; i < width; i++) {
		coordinateSystem.move(x + i, y);
		pencil.press();
	}
}
void Draw::vertical(int x, int y, int height) {
	for (int i = 0; i < height; i++) {
		coordinateSystem.move(x, y + i);
		pencil.press();
	}
}