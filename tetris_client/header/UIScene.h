#pragma once
#include "Canvas.h"
#include "Scene.h"
#include "UIElement.h"
class UIScene : public Scene {
/* backgound�� ����� ǥ���ϸ� ���ÿ� UIElement�� ���� ��ư�̳� text�Է� ���� �޴´�.
* action�� ���� ������ UIElement�� �����Ѵ�.
*/
using SceneNameHandler = string(*)(UIElement* selectedElement, State state);

protected:
	Canvas * background;
	UIElement* ui;
	string(*nextSceneNameHandler)(UIElement* selectedElement, State state);
public:
	UIScene(Canvas* background, UIElement* ui, SceneNameHandler nextSceneNameHandler): Scene(), background(background), ui(ui), nextSceneNameHandler(nextSceneNameHandler){}
	virtual string action() override{
		ui->draw();
		background->draw();
		while (true) {
			Key key = Input::getKey();
			if (key != -1){
				ui->keyInputHandler(key);
				if (ui->endCheck()) {
					string nextSceneName = nextSceneNameHandler(ui->getSelectedElement(), ui->getState());
					if (nextSceneName != "") {
						return nextSceneName;
					}
					else {

					}

				}

			}
			background->update();	// canvas�� update()�� ������ ȣ���Ͽ� ������ �̹����� �׷�����.
		}
	}

	~UIScene() {
		delete background;
	}
};