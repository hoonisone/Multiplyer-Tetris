#pragma once
#include "Scene.h"
#include "UserManager.h"

class ButtonScene : public Scene {	// 선택 될 때 까지 장면을 연출하다가 버튼이 선택되면 text를 반환하고 장렬히 전사
private:
	ButtonManager* bm;
	Canvas* canvas;
	virtual void erase() {
		bm->erase();
		canvas->erase();
	}
public:
	ButtonScene(ButtonManager* bm, Canvas* canvas) :bm(bm), canvas(canvas) {}
	virtual string start() override {
		bm->draw();
		canvas->draw();
		while (true) {
			char key = Input::getKey();
			if (key == -1) {
				continue;
			}
			switch (key) {
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
				return bm->click();
				break;
			default:
				bm->enter(key);
			}
			canvas->update();	// canvas의 동적 연출을 위해 무한히 호출해줌
		}
	}
	~ButtonScene() {
		delete bm;
		delete canvas;
	}
};