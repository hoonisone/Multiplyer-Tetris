#pragma once
#include "Scene.h"

/*
	ȭ�鿡 ��ư�� ����ϰ� ���ϴ� ��ư�� ���ù޴� Scene�̴�.
	��ư�� �ϴ��� �����Ǵ� ȭ�� �̸��� ������ �� �ִ�.
*/
class ButtonSelectScene : public Scene {	// ���� �� �� ���� ����� �����ϴٰ� ��ư�� ���õǸ� text�� ��ȯ�ϰ� ����� ����
private:
	UIElementManager* bm;
	Canvas* canvas;
	vector<string> buttonTexts;	// �ش� ��鿡�� ���õ� �� �ִ� ��ư�� ��� �̸��� ��´�.
	vector<string> sceneNames;	// �ε����� ¦�������� ��ư�� �ش��ϴ� ���� ����� �̸��� ��´�.
public:
	ButtonSelectScene(UIElementManager* bm, Canvas* canvas, vector<string> buttonTexts, vector<string> sceneNames) :
		bm(bm), canvas(canvas), buttonTexts(buttonTexts), sceneNames(sceneNames) {}
	virtual string action() override {
		bm->draw();
		canvas->draw();
		while (true) {
			char key = Input::getKey();
			if (key == -1) continue;	// Ű �Է��� ������ continue
			switch (key) {
			case KEY_UP:    bm->up();    break;
			case KEY_DOWN:  bm->down();  break;
			case KEY_LEFT:  bm->left();  break;
			case KEY_RIGHT: bm->right(); break;
			case KEY_SPACE:
				return getNextSceneName(bm->getSelectedButtonText());
			}
			canvas->update();	// canvas�� ���� ������ ���� ������ ȣ������
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