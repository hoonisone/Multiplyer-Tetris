#include "bean.h"
#include <vector>
#include "Canvas.h"
#include "ColorPainter.h"
#include "ColorPrinter.h"
#include "ButtonManager.h"

using namespace std;

SelectScene* ModeSelectScene() {
	return new SelectScene(ModeSelectSceneButtonManager({ "Single Mode", "Multi Mode", "Developer" }), MainSceneCanvas());
}
SelectScene* SingleModeMeneSelectScene() {
	return new SelectScene(ModeSelectSceneButtonManager({ "Start", "Rank" }), MainSceneCanvas());
}
ButtonManager* ModeSelectSceneButtonManager(vector<string> names) {
	ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
	ColorPainter painter({ "¡¤" }, WHITE, BLACK);
	ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
	ColorPainter selectPainter({ "¡¤" }, AQUA, BLACK);
	ButtonManager* bm = new ButtonManager(1, 3);
	int x = WIDTH / 2;
	int y = 20;
	int w = 15;
	int h = 5;
	for (int i = 0; i < names.size(); i++) {
		bm->enroll(new Button(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * i, w, h, names[i], painter.newObject(), printer.newObject(), selectPainter.newObject(), selectPrinter.newObject(), true), 0, i);
	}
	return bm;
}
Canvas* MainSceneCanvas() {
	vector<PointShape> letters = {
		{"¢Ë¢Ë¢Ë",
		 "  ¢Ë  ",
		 "  ¢Ë  ",
		 "  ¢Ë  ",
		 "  ¢Ë  "},

		{"¢Ë¢Ë¢Ë",
		 "¢Ë    ",
		 "¢Ë¢Ë¢Ë",
		 "¢Ë    ",
		 "¢Ë¢Ë¢Ë"},

		{"¢Ë¢Ë¢Ë",
		 "  ¢Ë  ",
		 "  ¢Ë  ",
		 "  ¢Ë  ",
		 "  ¢Ë  "},

		{"¢Ë¢Ë  ",
		 "¢Ë  ¢Ë",
		 "¢Ë¢Ë¢Ë",
		 "¢Ë  ¢Ë",
		 "¢Ë  ¢Ë"},

		{"¢Ë¢Ë¢Ë",
		 "  ¢Ë  ",
		 "  ¢Ë  ",
		 "  ¢Ë  ",
		 "¢Ë¢Ë¢Ë"},

		{"¢Ë¢Ë¢Ë",
		 "¢Ë    ",
		 "¢Ë¢Ë¢Ë",
		 "    ¢Ë",
		 "¢Ë¢Ë¢Ë"} };
	vector<ColorPainter> colorPainters;
	vector<Color> colors = { RED, YELLOW, GREEN, AQUA, BLUE, PURPLE };
	for (int i = 0; i < letters.size(); i++) {
		colorPainters.push_back(new ColorPainter(letters[i], colors[i], BLACK));
	}
	Canvas* canvas = new Canvas();
	int width = 100;
	int num = colorPainters.size();
	for (int i = 0; i < num; i++) {
		canvas->enrollFigure(colorPainters[i].newObject(), WIDTH / 2 - 30 + 10 * i, HEIGHT / 10 * 2);
	}
	return canvas;
}