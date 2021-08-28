#pragma once
#include <vector>
#include "Canvas.h"
#include "Scene.h"
#include "Block.h"
#include "BlockBoard.h"
#include "BlockCreator.h"
#include "SubScreen.h"
#include "scoreBoard.h"
#include "scoreManager.h"
#include "Tetris.h"

#include "FileManager.h"
#include "UserDao.h"
#include "UserManager.h"

#include "Scanner.h"
#include "ScannerCreator.h"

#include "UIScannerElement.h"
#include "UIElement.h"
#include "UIListElement.h"

#include "UIScene.h"
#include "TextInputScene.h"
#include "ButtonSelectScene.h"
#include "SingleModeGameScene.h"

#include "Director.h"

#include "singleScoreDao.h"
#include "SingleScoreManager.h"
string mainMenuSceneNextNameHandler(UIElement* element, State state) {
	static vector<string> key = { "Single Mode", "Multi Mode", "Developer", "Exit" };
	static vector<string> value = { "single menu scene", "server connection scene", "developer scene", "end scene" };
	string name = element->getName();
	for (int i = 0; i < key.size(); i++) {
		if (name == key[i]) {
			return value[i];
		}
	}
	return "";
}
string singleMenuSceneNextNameHandler(UIElement* element, State state) {
	static vector<string> key = { "Start", "Rank", "Back"};
	static vector<string> value = { "single game scene", "single rank scene", "main menu scene"};
	string name = element->getName();
	for (int i = 0; i < key.size(); i++) {
		if (name == key[i]) {
			return value[i];
		}
	}
	return "";
}

string serverConnectionSceneNextNameHandler(UIElement* element, State state) {
	string name = element->getName();
	if (name == "Back") {
		return "main menu scene";
	}
	else if(name == "Connect"){
		cout << state[0].second << endl;
		cout << state[1].second << endl;
		return "";
	}
	return "";
}
class Bean {
public:
	//// Director
	//static Director* getDirector() {
	//	Director* director = new Director();
	//	director->enrollScene("main menu", getMainMenuScene);
	//	director->enrollScene("single menu", getSingleMenuScene);
	//	director->enrollScene("server connect", getServerSelectScene);
	//	director->enrollScene("single game", getSingleGameScene);
	//	return director;
	//}
	//// Scene
	//static Scene* getButtonSelectScene(vector<string> buttonNames, vector<string> nextSceneNames) {
	//	UIManager* buttonManager = getModeSelectSceneButtonManager(buttonNames);
	//	Canvas* canvas = getMainSceneCanvas();
	//	return new ButtonSelectScene(buttonManager, canvas, buttonNames, nextSceneNames);
	//}
	//static Scene* getTextInputScene(UIManager* buttonManager, Canvas* canvas) {
	//	return new TextInputScene(buttonManager, canvas, "main mune");
	//}
	//static Scene* getSingleMenuScene() {
	//	const vector<string> buttonNames = { "Start", "Rank", "Back" };
	//	const vector<string> nextSceneNames = { "single game", "single rank", "main menu" };
	//	return getButtonSelectScene(buttonNames, nextSceneNames);
	//}
	//static Scene* getMainMenuScene() {
	//	vector<string> buttonNames = { "Single Mode", "Multi Mode", "Developer", "Exit" };
	//	vector<string> nextSceneNames = { "single menu", "server connect", "developer", "game exit" };
	//	return getButtonSelectScene(buttonNames, nextSceneNames);
	//}
	//static Scene* getServerSelectScene() {
	//	return getTextInputScene(getServerSelectButtonManager(), getMainSceneCanvas());
	//}
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//static UIManager* getModeSelectSceneButtonManager(vector<string> names) {
	//	ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
	//	ColorPainter painter({ "˚" }, WHITE, BLACK);
	//	ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
	//	ColorPainter selectPainter({ "˚" }, AQUA, BLACK);
	//	UIManager* bm = new UIManager(0, 0, 0, 0, 1, names.size());
	//	int x = WIDTH / 2;
	//	int y = 20;
	//	int w = 20;
	//	int h = 5;
	//	for (int i = 0; i < names.size(); i++) {
	//		bm->enroll(new UITextBlock(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * i, w, h, names[i], painter.getCopy(), printer.newObject(), selectPainter.getCopy(), selectPrinter.newObject(), true), 0, i);
	//	}
	//	return bm;
	//}
	//static UIManager* getServerSelectButtonManager() {
	//	vector<string> names = { "IP", "PORT" };
	//	ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
	//	ColorPainter painter({ "˚" }, WHITE, BLACK);
	//	ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
	//	ColorPainter selectPainter({ "˚" }, AQUA, BLACK);
	//	UIManager* bm = new UIManager(0, 0, 0, 0, 3, names.size() + 2);
	//	int x = WIDTH / 2;
	//	int y = 20;
	//	int w = 20;
	//	int h = 5;
	//	for (int i = 0; i < names.size(); i++) {
	//		bm->enroll(getScannerButton(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * i, w, h), 2, i);
	//		bm->enroll(new UITextBlock(x - w * painter.getWidth() / 2 - 8, y + (h - 1) * painter.getHeight() * i, 4, h, names[i], painter.getCopy(), printer.newObject(), selectPainter.getCopy(), selectPrinter.newObject(), false), 0, i);
	//	}
	//	bm->enroll(getButton(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * names.size(), w, h, "Connect", true), 2, names.size());
	//	bm->enroll(getButton(x - w * painter.getWidth() / 2, y + (h - 1) * painter.getHeight() * (names.size() + 1), w, h, "Back", true), 2, names.size() + 1);
	//	return bm;
	//}
	//static Scanner* getScanner(int x, int y, int width, int height) {
	//	return new Scanner(x, y, width, height, new ColorPrinter(CENTER, MIDDLE, WHITE));
	//}
	//static UIElement* getScannerButton(int x, int y, int w, int h) {
	//	ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
	//	ColorPainter painter({ "˚" }, WHITE, BLACK);
	//	ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
	//	ColorPainter selectPainter({ "˚" }, AQUA, BLACK);
	//	return new UIScannerBlock(x, y, w, h, getScannerScreator(), painter.getCopy(), printer.newObject(), selectPainter.getCopy(), selectPrinter.newObject(), true);
	//}
	//static UITextBlock* getButton(int x, int y, int w, int h, string text, bool borderFlag) {
	//	ColorPrinter printer(CENTER, MIDDLE, WHITE, BLACK);
	//	ColorPainter painter({ "˚" }, WHITE, BLACK);
	//	ColorPrinter selectPrinter(CENTER, MIDDLE, AQUA, BLACK);
	//	ColorPainter selectPainter({ "˚" }, AQUA, BLACK);
	//	return new UITextBlock(x, y, w, h, text, painter.getCopy(), printer.newObject(), selectPainter.getCopy(), selectPrinter.newObject(), borderFlag);
	//}
	//static FileManager* getUserFileManager() {
	//	return new FileManager("user.txt");
	//}
	//static UserDao* getUserDao() {
	//	return new UserDao(getUserFileManager());
	//}
	//static UserManager* getUserManager() {
	//	return new UserManager(getUserDao());
	//}

	static FileManager* getSingleScoreFileManager() {
		return new FileManager("single mode score.txt");
	}
	static SingleScoreDao* getSingleScoreDao() {
		return new SingleScoreDao(getSingleScoreFileManager());
	}
	static SingleScoreManager* getSingleScoreManager() {
		return new SingleScoreManager(getSingleScoreDao());
	}

	static ScannerCreator* getScannerCreator() {
		return new ScannerCreator();
	}
	static UIScannerElement* getUIScannerBlock(int x, int y, int w, int h, string name) {
		ColorPainter* spainter = new ColorPainter({ "˚" }, AQUA, BLACK);
		ColorPainter* upainter = new ColorPainter({ "˚" }, WHITE, BLACK);
		ColorPrinter* sprinter = new ColorPrinter(CENTER, MIDDLE, AQUA, BLACK);
		ColorPrinter* uprinter = new ColorPrinter(CENTER, MIDDLE, WHITE, BLACK);
		return new UIScannerElement(x, y, w, h, name, getScannerCreator(), spainter, upainter, sprinter, uprinter);
	}
	static UIElement* getNunTerminalUIElement(int x, int y, int w, int h, int mapW, int mapH) {
		UIElement* element = getTerminalUIElement(x, y, w, h, "", mapW, mapH);
		element->setTerminalFlag(false); // terminal 설정 취소
		element->setBorderFlag(false); // numTerminal은 border를 기본적으로 그리지 않음
		return element;
	}
	static UIElement* getTerminalUIElement(int x, int y, int w, int h, string text, int mapW, int mapH) {
		ColorPainter* spainter = new ColorPainter({ "˚" }, AQUA, BLACK);
		ColorPainter* upainter = new ColorPainter({ "˚" }, WHITE, BLACK);
		ColorPrinter* sprinter = new ColorPrinter(CENTER, MIDDLE, AQUA, BLACK);
		ColorPrinter* uprinter = new ColorPrinter(CENTER, MIDDLE, WHITE, BLACK);
		return new UIElement(x, y, w, h, text, spainter, upainter, sprinter, uprinter, true, mapW, mapH);
	}
	static UIElement* getUIVerticalTextListElement(int x, int y, int ew, int eh, vector<string> names) {
		UIElement* parent = getNunTerminalUIElement(x - ew / 2, y, ew, (eh-1)* names.size()+1, 1, names.size());
		for (int i = 0; i < names.size(); i++) {
			parent->enroll(getTerminalUIElement(0, (eh - 1) * i, ew, eh, names[i], 0, 0), 0, i);
		}
		return parent;
	}
	static UIElement* getMainMenuUI() {	// UI for 메인 메뉴 화면
		int x = WIDTH / 2;
		int y = 20;
		int ew = 20;
		int eh = 5;
		return getUIVerticalTextListElement(x, y, ew, eh, { "Single Mode", "Multi Mode", "Developer", "Exit" });
	}
	static UIElement* getSingleMenuUI() {	// UI for 메인 메뉴 화면
		int x = WIDTH / 2;
		int y = 20;
		int ew = 20;
		int eh = 5;
		return getUIVerticalTextListElement(x, y, ew, eh, { "Start", "Rank", "Back" });
	}
	static UIElement* getServerConnectionUI() {
		int x = WIDTH / 2;
		int y = 20;
		int ew = 20;
		int eh = 5;
		int en = 4;
		UIElement* parent = getNunTerminalUIElement(x - ew, y, ew, (eh - 1) * en+1, 3, en);

		parent->enroll(getTerminalUIElement(0, (eh - 1) * 0, ew, eh, "IP ADDRESS:", 0, 0), 0, 0, false, false);
		parent->enroll(getTerminalUIElement(0, (eh - 1) * 1, ew, eh, "PORT NUMBER:", 0, 0), 0, 1, false, false);

		parent->enroll(getUIScannerBlock(ew-2, (eh - 1) * 0, ew, eh, "ip"), 2, 0, true, true);
		parent->enroll(getUIScannerBlock(ew-2, (eh - 1) * 1, ew, eh, "port"), 2, 1);
		parent->enroll(getTerminalUIElement(ew-2, (eh - 1) * 2, ew, eh, "Connect", 0, 0), 2, 2);
		parent->enroll(getTerminalUIElement(ew-2, (eh - 1) * 3, ew, eh, "Back", 0, 0), 2, 3);

		return parent;
	}
	static UIElement* getUIListElement(int x, int y, int len) {
		ColorPainter* spainter = new ColorPainter({ "˚" }, AQUA, BLACK);
		ColorPainter* upainter = new ColorPainter({ "˚" }, WHITE, BLACK);
		ColorPrinter* sprinter = new ColorPrinter(CENTER, MIDDLE, AQUA, BLACK);
		ColorPrinter* uprinter = new ColorPrinter(CENTER, MIDDLE, WHITE, BLACK);
		return new UIListElement(x, y, len, spainter, upainter, sprinter, uprinter);
	}
	static UIElement* getRankUIListElementUI(vector<SingleScore> &scores) {
		int x = WIDTH / 2-50;
		int y = 10;
		UIElement* element = getNunTerminalUIElement(x, y, 0, 0, 1, scores.size());
		for (int i = 0; i < scores.size(); i++) {
			element->enroll(getSingleScoreUIElement(0, 2 * i, scores[i], i + 1), 0, i);
		}
		return element;
	}
	static UIElement* getSingleScoreUIElement(int x, int y, SingleScore score, int rank) {
		UIElement* element = getTerminalUIElement(x, y, 94, 3, "", 4, 1);	// 부모 입장에서는 terminal 처럼 보이나 내부적으로 여러 요소를 갖는다. -> 테이블 모습을 취하기 위함
		//element->setBorderFlag(false);
		element->enroll(getTerminalUIElement(0 , 0,  10, 3, to_string(rank), 0, 0), 0, 0);
		element->enroll(getTerminalUIElement(8 , 0, 20, 3, to_string(score.getScore()), 0, 0), 1, 0);
		element->enroll(getTerminalUIElement(26, 0, 30, 3, score.getName(), 0, 0), 2, 0);
		element->enroll(getTerminalUIElement(54, 0, 40, 3, score.getDate(), 0, 0), 3, 0);
		return element;
	}
	static UIElement* getSingleRankUI() {
		UIElement* parent = getNunTerminalUIElement(0, 0, 0, 0, 2, 1);
		UIElement* scoreList = Bean::getRankUIListElementUI(Bean::getSingleScoreManager()->data);
		parent->enroll(getTerminalUIElement(0, 0, 20, 5, "Back", 0, 0), 0, 0);
		parent->enroll(scoreList, 1, 0);
		return parent;
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
	static Director* getDirector() {
		Director* director = new Director();
		director->enrollScene("main menu scene", getMainMenuUIScene);
		director->enrollScene("single menu scene", getSingleMenuUIScene);
		director->enrollScene("single game scene", getSingleGameScene);
		director->enrollScene("server connection scene", getServerConnectionScene);
		
		return director;
	}
	static Scene* getMainMenuUIScene() {
		return getUIScene(getMainMenuUI(), mainMenuSceneNextNameHandler);
	}
	static Scene* getUIScene(UIElement* element, string(*nextSceneNameHandler)(UIElement* element, State state)) {
		Canvas* canvas = getMainSceneCanvas();
		return new UIScene(canvas, element, nextSceneNameHandler);
	}
	static Scene* getSingleMenuUIScene() {
		return getUIScene(getSingleMenuUI(), singleMenuSceneNextNameHandler);
	}
	static Scene* getSingleGameScene() {
		return new SingleModeGameScene(getTetris(), "main menu scene");
	}
	static Scene* getServerConnectionScene() {
		return getUIScene(getServerConnectionUI(), serverConnectionSceneNextNameHandler);
	}

	//Tetris
	static Tetris* getTetris(){
	return new Tetris(getMainScreen(), getSubScreen(), getRandomBlockCreator(), getScoreManager());
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
	static ScoreBoard* getScoreBoard() {
		return new ScoreBoard(34, new ColorPainter({ "·" }));
	}
	static ScoreManager* getScoreManager() {
		return new ScoreManager(getScoreBoard());
	}
};

