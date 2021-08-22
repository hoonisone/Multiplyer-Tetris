#pragma once
#include "Scene.h"

/*
	화면에 버튼을 출력하고 원하는 버튼만 선택받는 Scene이다.
	버튼에 일대일 대응되는 화면 이름을 세팅할 수 있다.
*/
class ButtonSelectScene : public Scene {	// 선택 될 때 까지 장면을 연출하다가 버튼이 선택되면 text를 반환하고 장렬히 전사
private:
	UIElementManager* bm;
	Canvas* canvas;
	vector<string> buttonTexts;	// 해당 장면에서 선택될 수 있는 버튼의 모든 이름을 담는다.
	vector<string> sceneNames;	// 인덱스로 짝지어지는 버튼에 해당하는 다음 장면의 이름을 담는다.
public:
	ButtonSelectScene(UIElementManager* bm, Canvas* canvas, vector<string> buttonTexts, vector<string> sceneNames) :
		bm(bm), canvas(canvas), buttonTexts(buttonTexts), sceneNames(sceneNames) {}
	virtual string action() override {
		bm->draw();
		canvas->draw();
		while (true) {
			char key = Input::getKey();
			if (key == -1) continue;	// 키 입력이 없으면 continue
			switch (key) {
			case KEY_UP:    bm->up();    break;
			case KEY_DOWN:  bm->down();  break;
			case KEY_LEFT:  bm->left();  break;
			case KEY_RIGHT: bm->right(); break;
			case KEY_SPACE:
				return getNextSceneName(bm->getSelectedButtonText());
			}
			canvas->update();	// canvas의 동적 연출을 위해 무한히 호출해줌
		}
	}
	string getNextSceneName(string selectedButtonText) {
		for (int i = 0; i < buttonTexts.size(); i++) {
			if (selectedButtonText == buttonTexts[i])
				return sceneNames[i];
		}
		errorPrint("button name does not exist in list(buttonTexts)");
	}
	~ButtonSelectScene() {
		delete bm;
		delete canvas;
	}
};