#pragma once
#include "Canvas.h"
#include "Scene.h"
#include "UIElement.h"
class UIScene : public Scene {
/* backgound로 배경을 표현하며 동시에 UIElement를 통해 버튼이나 text입력 등을 받는다.
* action의 종료 시점은 UIElement가 결정한다.
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
			background->update();	// canvas는 update()를 무한히 호출하여 동적인 이미지를 그려낸다.
		}
	}

	~UIScene() {
		delete background;
	}
};