#pragma once

#include "Scene.h"

class SelectScene : public Scene {	// ���� �� �� ���� ����� �����ϴٰ� ��ư�� ���õǸ� text�� ��ȯ�ϰ� ����� ����
private:
	ButtonManager* bm;
	Canvas* canvas;
	virtual void erase() {
		bm->erase();
		canvas->erase();
	}
public:
	SelectScene(ButtonManager* bm, Canvas* canvas) :bm(bm), canvas(canvas) {}
	virtual string start() override {
		bm->draw();
		canvas->draw();
		while (true) {
			switch (Input::getKey()) {
			case KEY_UP:
				bm->up();
				bm->draw();
				break;
			case KEY_DOWN:
				bm->down();
				bm->draw();
				break;
			case KEY_LEFT:
				bm->left();
				bm->draw();
				break;
			case KEY_RIGHT:
				bm->right();
				bm->draw();
				break;
			case KEY_SPACE:
				erase();
				return bm->getSelectedButtonText();
				break;
			}

			canvas->update();	// canvas�� ���� ������ ���� ������ ȣ������
		}
	}
	~SelectScene() {
		delete bm;
		delete canvas;
	}
};