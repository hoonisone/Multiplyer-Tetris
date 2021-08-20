#pragma once
#include "Button.h"
#include "error.h"
#include "string+.h"
#include <vector>
using namespace std;
/*
키 입력을 받아 버튼을 선택 동작 시킨다.
방향키는 버튼 이동(선택)
스페이스는 버튼 클릭(선택된 버튼 정보를 반환한다.)
나머지 키는 버튼에게 넘겨 핸들링한다.
*/
class ButtonManager {
private:
	int width, height;
	int x = 0, y = 0;
	vector<vector<Button*>> map;
	vector<Button*> buttons;
	bool rangeCheck(int x, int y) {return 0 <= x && x < width && 0 <= y && y < height;}
	bool existCheck(int x, int y) { return map[y][x] != NULL; }
	void select(int x, int y, bool redraw = true) {
		if (existCheck(this->x, this->y)) {
			map[this->y][this->x]->unselect(redraw);
		}
		this->x = x;
		this->y = y;
		map[this->y][this->x]->select(redraw);
	}
	void moveCursor(int x, int y, bool redraw = true) {
		if (rangeCheck(x, y) && existCheck(x, y)) {
			select(x, y, redraw);
		}   
	}
	string (*action)(ButtonManager* button) = NULL;
public:
	vector<Button*> getButtons() {
		return buttons;
	}
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
	void setAction(string (*action)(ButtonManager* button)) {
		this->action = action;
	}
	void up(bool redraw = true) {
		moveCursor(x, y - 1, redraw);
	}
	void down(bool redraw = true) {
		moveCursor(x, y + 1, redraw);
	}
	void right(bool redraw = true) {
		moveCursor(x+1, y, redraw);
	}
	void left(bool redraw = true) {
		moveCursor(x-1, y, redraw);
	}
	string click() {// 버튼 기능을 활성화 하고 정보를 반환
		if (existCheck(this->x, this->y)) {
			if (action != NULL) {
				return action(this);	// buttonManager에 action이 등록되어있다면 이를 우선으로 수행
			}
			else {
				return map[this->y][this->x]->click();	// buttonManager에 action이 없다면 button의 action을 수행
			}
		}
	}
	string getSelectedButtonText() {	// 현재 선택된 버튼의 텍스트 반환
		if (!rangeCheck(x, y) || !existCheck(x, y)) {
			char errorBuffer[100];
			sprintf(errorBuffer, "can not get button text in (%d, %d)", x, y);
			errorPrint(errorBuffer);
		}
		return map[this->y][this->x]->getText();
	}
	void update(char input, bool redraw = true) {
		map[this->y][this->x]->update(input, redraw);
	}
	~ButtonManager() {
		for (int i = 0; i < buttons.size(); i++) {
			delete buttons[i];
		}
	}
	void erase() {
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i]->erase();
		}
	}
};