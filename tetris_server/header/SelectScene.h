#pragma once

#include "Scene.h"

class SelectScene : public Scene {	// 선택 될 때 까지 장면을 연출하다가 버튼이 선택되면 text를 반환하고 장렬히 전사
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

			canvas->update();	// canvas의 동적 연출을 위해 무한히 호출해줌
		}
	}
	~SelectScene() {
		delete bm;
		delete canvas;
	}
};