#pragma once
#include "tetris.h"
#include "Input.h"

class SingleModeGameManger {
	Tetris* tetris;
public:
	SingleModeGameManger(Tetris* tetris) :tetris(tetris) {};
	void run() {
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
	}
	~SingleModeGameManger() {
		delete tetris;
	}
};