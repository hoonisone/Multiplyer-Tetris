#pragma once
#include "tetris.h"
#include "Scene.h"

class SingleModeGameScene:public Scene {
	Tetris* tetris;
	string nextSceneName;
public:
	SingleModeGameScene(Tetris* tetris, string nextSceneName) :tetris(tetris), nextSceneName(nextSceneName) {};
	string action() {
		tetris->draw(0, 0);
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
	}
};