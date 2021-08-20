#pragma once
#include <vector>
#include "ButtonManager.h"
#include "Canvas.h"
#include "Scene.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "SubScreen.h"
#include "ButtonSelectScene.h"
#include "TextInputScene.h"
#include "scoreBoard.h"
#include "scoreManager.h"
#include "Tetris.h"
#include "SingleModeGameScene.h"
#include "Scanner.h"
#include "ScannerButton.h"
#include "FileManager.h"
#include "UserDao.h"
#include "UserManager.h"
#include "Director.h"

string ServerSelectButtonManagerAction(ButtonManager* bm) {
	string text = bm->getSelectedButtonText();
	if(text  == "Connect") {
		vector<Button*> buttons = bm->getButtons();
		string ip = buttons[0]->getText();
		string port = buttons[2]->getText();
		/*return ip + "/" + port;*/
		// 연결 하기 작성해야 함
		bool connectedFlag = false;
		if (connectedFlag) {
			return "Success";
		}
		else {
			return "Fail";
		}
	}
	else if (text == "Back") {
		return text;
	}
	return "Fail";
}
string ReturnSelectedButtonTextAction(ButtonManager * bm) {
	return bm->getSelectedButtonText();
}
class Bean {
public:
	// Director
	static Director* getDirector() {
		Director* director = new Director();
		director->enrollScene("main menu", getMainMenuScene);
		director->enrollScene("single menu", getSingleMenuScene);
		director->enrollScene("server connect", getServerSelectScene);
		director->enrollScene("single game", getSingleGameScene);
		return director;
	}
	// Scene
	static Scene* getButtonSelectScene(vector<string> buttonNames, vector<string> nextSceneNames) {
		ButtonManager* buttonManager = getModeSelectSceneButtonManager(buttonNames);
		Canvas* canvas = getMainSceneCanvas();
		return new ButtonSelectScene(buttonManager, canvas, buttonNames, nextSceneNames);
	}
	static Scene* getTextInputScene(ButtonManager* buttonManager, Canvas* canvas) {
		return new TextInputScene(buttonManager, canvas, "main mune");
	}

	static Scene* getSingleMenuScene() {
		const vector<string> buttonNames = { "Start", "Rank", "Back" };
		const vector<string> nextSceneNames = { "single game", "single rank", "main menu" };
		return getButtonSelectScene(buttonNames, nextSceneNames);
	}
	static Scene* getMainMenuScene() {
		vector<string> buttonNames = { "Single Mode", "Multi Mode", "Developer", "Exit" };
		vector<string> nextSceneNames = { "single menu", "server connect", "developer", "game exit" };
		return getButtonSelectScene(buttonNames, nextSceneNames);
	}
	static Scene* getServerSelectScene() {
		return getTextInputScene(getServerSelectButtonManager(), getMainSceneCanvas());
	}
	static Scene* getSingleGameScene() {
		return new SingleModeGameScene(getTetris(), "main menu");
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	static ButtonManager* getModeSelectSceneButtonManager(vector<string> names) {
		ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
		ColorPainter painter({ "˚" }, WHITE, BLACK);
		ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
		ColorPainter selectPainter({ "˚" }, AQUA, BLACK);
		ButtonManager* bm = new ButtonManager(1, names.size());
		int x = WIDTH / 2;
		int y = 20;
		int w = 20;
		int h = 5;
		for (int i = 0; i < names.size(); i++) {
			bm->enroll(new Button(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * i, w, h, names[i], painter.getCopy(), printer.newObject(), selectPainter.getCopy(), selectPrinter.newObject(), true), 0, i);
		}
		bm->setAction(ReturnSelectedButtonTextAction);

		return bm;
	}
	static ButtonManager* getServerSelectButtonManager() {
		vector<string> names = { "IP", "PORT" };
		ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
		ColorPainter painter({ "˚" }, WHITE, BLACK);
		ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
		ColorPainter selectPainter({ "˚" }, AQUA, BLACK);
		ButtonManager* bm = new ButtonManager(3, names.size() + 2);
		int x = WIDTH / 2;
		int y = 20;
		int w = 20;
		int h = 5;
		for (int i = 0; i < names.size(); i++) {
			bm->enroll(getScannerButton(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * i, w, h), 2, i);
			bm->enroll(new Button(x - w * painter.getWidth() / 2 - 8, y + (h - 1) * painter.getHeight() * i, 4, h, names[i], painter.getCopy(), printer.newObject(), selectPainter.getCopy(), selectPrinter.newObject(), false), 0, i);
		}
		bm->enroll(getButton(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * names.size(), w, h, "Connect", true), 2, names.size());
		bm->enroll(getButton(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * (names.size() + 1), w, h, "Back", true), 2, names.size() + 1);
		bm->setAction(ServerSelectButtonManagerAction);
		return bm;
	}
	static Canvas* getMainSceneCanvas() {
		vector<PointShape> letters = {
			{"▦▦▦",
			 "  ▦  ",
			 "  ▦  ",
			 "  ▦  ",
			 "  ▦  "},

			{"▦▦▦",
			 "▦    ",
			 "▦▦▦",
			 "▦    ",
			 "▦▦▦"},

			{"▦▦▦",
			 "  ▦  ",
			 "  ▦  ",
			 "  ▦  ",
			 "  ▦  "},

			{"▦▦  ",
			 "▦  ▦",
			 "▦▦▦",
			 "▦  ▦",
			 "▦  ▦"},

			{"▦▦▦",
			 "  ▦  ",
			 "  ▦  ",
			 "  ▦  ",
			 "▦▦▦"},

			{"▦▦▦",
			 "▦    ",
			 "▦▦▦",
			 "    ▦",
			 "▦▦▦"} };
		vector<ColorPainter> colorPainters;
		vector<Color> colors = { RED, YELLOW, GREEN, AQUA, BLUE, PURPLE };
		for (int i = 0; i < letters.size(); i++) {
			colorPainters.push_back(new ColorPainter(letters[i], colors[i], BLACK));
		}
		Canvas* canvas = new Canvas();
		int width = 100;
		int num = colorPainters.size();
		for (int i = 0; i < num; i++) {
			canvas->enrollFigure(colorPainters[i].getCopy(), WIDTH / 2 - 30 + 10 * i, HEIGHT / 10 * 2);
		}
		return canvas;
	}
	static BlockBoard* getBlockBoard() {
		return new BlockBoard(2, 1, 10, 20);
	}
	static BlockCreator* getRandomBlockCreator() {
		return new SamePointBlockCreator({ "■"});
	}
	static MainScreen* getMainScreen() {
		return new MainScreen(getBlockBoard(), getRandomBlockCreator()->createBlock(), getMainScreenPainter());
	}
	static ColorPainter* getMainScreenPainter() {
		return new ColorPainter({ "˚" }, AQUA);
	}
	static SubScreen* getSubScreen() {
		Block* block = getRandomBlockCreator()->createBlock();
		ColorPainter* painter = new ColorPainter({ "˚"}, AQUA);
		return new SubScreen(2*painter->getWidth()+BLOCK_WIDTH*block->getPainter()->getWidth(), 2 * painter->getHeight()+ 20*block->getPainter()->getHeight(), block, painter);
	}
	static Tetris* getTetris(){
		return new Tetris(getMainScreen(), getSubScreen(), getRandomBlockCreator(), getScoreManager());
	}
	static ScoreBoard* getScoreBoard() {
		return new ScoreBoard(34, new ColorPainter({ "·" }));
	}
	static ScoreManager* getScoreManager() {
		return new ScoreManager(getScoreBoard());
	}

	static Scanner* getScanner(int x, int y, int width, int height) {
		return new Scanner(x, y, width, height, new ColorPrinter(CENTER, MIDDLE, WHITE));
	}
	static Button* getScannerButton(int x, int y, int w, int h) {
		ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
		ColorPainter painter({ "˚" }, WHITE, BLACK);
		ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
		ColorPainter selectPainter({ "˚" }, AQUA, BLACK);
		return new ScannerButton(x, y, getScanner(x + 1, y + 1, w - 2 * painter.getWidth(), h - 2 * painter.getHeight()), painter.getCopy(), printer.newObject(), selectPainter.getCopy(), selectPrinter.newObject(), true);
	}
	static Button* getButton(int x, int y, int w, int h, string text, bool borderFlag) {
		ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
		ColorPainter painter({ "˚" }, WHITE, BLACK);
		ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
		ColorPainter selectPainter({ "˚" }, AQUA, BLACK);
		return new Button(x, y, w, h, text, painter.getCopy(), printer.newObject(), selectPainter.getCopy(), selectPrinter.newObject(), borderFlag);
	}
	static FileManager* getUserFileManager() {
		return new FileManager("user.txt");
	}
	static UserDao* getUserDao() {
		return new UserDao(getUserFileManager());
	}
	static UserManager* getUserManager() {
		return new UserManager(getUserDao());
	}
};

