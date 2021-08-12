#pragma once
#include <vector>
#include "ButtonManager.h"
#include "Canvas.h"
#include "Scene.h"
#include "SelectScene.h"
#include "BlockBoard.h"
#include "BlockCreator.h"

class Bean {
public:
	static SelectScene* getModeSelectScene() {
		return new SelectScene(getModeSelectSceneButtonManager({ "Single Mode", "Multi Mode", "Developer" }), getMainSceneCanvas());
	}
	static SelectScene* getSingleModeMeneSelectScene() {
		return new SelectScene(getModeSelectSceneButtonManager({ "Start", "Rank" }), getMainSceneCanvas());
	}
	static ButtonManager* getModeSelectSceneButtonManager(vector<string> names) {
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
	static Canvas* getMainSceneCanvas() {
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
	static BlockBoard* getBlockBoard() {
		return new BlockBoard(4, 2);
	}
	static BlockCreator* getRandomBlockCreator() {
		return new SamePointBlockCreator({ "¢Ë¢Ë", "¢Ë¢Ë" });
	}
	static MainScreen* getMainScreen() {
		return new MainScreen(getRandomBlockCreator(), getBlockBoard(), getMainScreenPainter());
	}
	static ColorPainter* getMainScreenPainter() {
		return new ColorPainter({ "¡¤"});
	}
};