#pragma once
#include "tetris.h"
#include "Scene.h"
#include "Consol.h"
class SingleModeGameScene:public Scene {
	Tetris* tetris;
	string nextSceneName;
	Canvas* canvas;
public:
	SingleModeGameScene(Canvas* canvas, Tetris* tetris, string nextSceneName) :canvas(canvas), tetris(tetris), nextSceneName(nextSceneName) {};
	string action() {
		tetris->draw(WIDTH/2-tetris->getWidth()/2, 15);
		canvas->draw();
		while (!tetris->checkEnd()) {
			tetris->update();
			switch (Input::getKey()) {
			case KEY_UP:
				tetris->turnRight();
				break;
			case KEY_DOWN:
				tetris->moveDown();
				break;
			case KEY_RIGHT:
				tetris->moveRight();
				break;
			case KEY_LEFT:
				tetris->moveLeft();
				break;
			case KEY_SPACE:
				tetris->dragDown();
				break;
			case 'c':
				tetris->hold();
				break;
			}
		}
		return nextSceneName;
	}
	~SingleModeGameScene() {
		delete tetris;
		delete canvas;
	}
};