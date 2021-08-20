#pragma once
#pragma once
#include "Scene.h"
#include "UserManager.h"

/*
	화면에 버튼을 출력하고 원하는 버튼만 선택받는 Scene이다.
	버튼에 일대일 대응되는 화면 이름을 세팅할 수 있다.
*/
class TextInputScene : public Scene {	// 선택 될 때 까지 장면을 연출하다가 버튼이 선택되면 text를 반환하고 장렬히 전사
private:
	ButtonManager* bm;
	Canvas* canvas;
public:
	TextInputScene(ButtonManager* bm, Canvas* canvas, string nextSceneName) :bm(bm), canvas(canvas) {}
	virtual string action() override {
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
				return "main menu";
				break;
			default:
				bm->update(key);
			}
			canvas->update();	// canvas의 동적 연출을 위해 무한히 호출해줌
		}
	}
	~TextInputScene() {
		delete bm;
		delete canvas;
	}
};