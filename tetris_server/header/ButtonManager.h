#pragma once
#include "Button.h"
#include "error.h"
#include "string+.h"
#include <vector>
using namespace std;

class ButtonManager {
private:
	int width, height;
	int x = 0, y = 0;
	vector<vector<Button*>> map;
	vector<Button*> buttons;
	bool rangeCheck(int x, int y) {return 0 <= x < width && 0 <= y && y < height;}
	bool existCheck(int x, int y) { return map[y][x] != NULL; }
	void select(int x, int y) {
		if (existCheck(this->x, this->y)) {
			map[this->y][this->x]->unselect();
		}
		this->x = x;
		this->y = y;
		map[this->y][this->x]->select();
	}
	void move(int x, int y) {
		if (rangeCheck(x, y) && existCheck(x, y)) {
			select(x, y);
		}
	}
	void (*action)(Button* button) = NULL;
public:
	ButtonManager(int width, int height):width(width), height(height) {
		map = vector<vector<Button*>>(height, vector<Button*>(width, NULL));
	}
	void enroll(Button* button, int x, int y, bool selectFlag = false) {
		if (!rangeCheck(x, y) || existCheck(x, y)) {
			char errorBuffer[100];
			sprintf(errorBuffer, "can not enroll button in (%d, %d)", x, y);
			errorPrint(errorBuffer);
		}
		buttons.push_back(button);
		map[y][x] = button;
		if (buttons.size() == 1 || selectFlag) {	// 처음으로 등록한 버튼이 클린 된 것으로 간주
			select(x, y);
		}
	}
	void draw()const {
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i]->draw();
		}
		map[this->y][this->x]->draw();	// 선택된 버튼을 맨 위로 올리기 위해 다시 한번 그리기
	}
	void setAction(void (*action)(Button* button)) {
		this->action = action;
	}
	void up() {
		move(x, y - 1);
	}
	void down() {
		move(x, y + 1);
	}
	void right() {
		move(x+1, y);
	}
	void left() {
		move(x-1, y);
	}
	void click() {
		if (existCheck(this->x, this->y)) {
			if (action != NULL) {
				action(map[this->y][this->x]);	// buttonManager에 action이 등록되어있다면 이를 우선으로 수행
			}
			else {
				map[this->y][this->x]->click();	// buttonManager에 action이 없다면 button의 action을 수행
			}
		}
	}
	~ButtonManager() {
		for (int i = 0; i < buttons.size(); i++) {
			delete buttons[i];
		}
	}
};