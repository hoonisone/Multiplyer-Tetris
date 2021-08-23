#pragma once
#include "Canvas.h"
#include "Scene.h"
#include "UIElement.h"
class UIScene : public Scene {
/* backgound�� ����� ǥ���ϸ� ���ÿ� UIElement�� ���� ��ư�̳� text�Է� ���� �޴´�.
* action�� ���� ������ UIElement�� �����Ѵ�.
*/
protected:
	Canvas * background;
	UIElement* ui;
public:
	UIScene(Canvas* background, UIElement* ui): background(background), ui(ui){}
	virtual string action() override{
		ui->draw();
		background->draw();
		while (true) {
			Key key = Input::getKey();
			if (key != -1){
				ui->keyInputHandler(key);
			}
			background->update();	// canvas�� update()�� ������ ȣ���Ͽ� ������ �̹����� �׷�����.
		}
	}

	~UIScene() {
		delete background;
	}
};