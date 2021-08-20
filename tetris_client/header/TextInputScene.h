#pragma once
#pragma once
#include "Scene.h"
#include "UserManager.h"

/*
	ȭ�鿡 ��ư�� ����ϰ� ���ϴ� ��ư�� ���ù޴� Scene�̴�.
	��ư�� �ϴ��� �����Ǵ� ȭ�� �̸��� ������ �� �ִ�.
*/
class TextInputScene : public Scene {	// ���� �� �� ���� ����� �����ϴٰ� ��ư�� ���õǸ� text�� ��ȯ�ϰ� ����� ����
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
			canvas->update();	// canvas�� ���� ������ ���� ������ ȣ������
		}
	}
	~TextInputScene() {
		delete bm;
		delete canvas;
	}
};