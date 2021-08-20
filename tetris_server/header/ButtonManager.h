#pragma once
#include "Button.h"
#include "error.h"
#include "string+.h"
#include <vector>
using namespace std;
/*
Ű �Է��� �޾� ��ư�� ���� ���� ��Ų��.
����Ű�� ��ư �̵�(����)
�����̽��� ��ư Ŭ��(���õ� ��ư ������ ��ȯ�Ѵ�.)
������ Ű�� ��ư���� �Ѱ� �ڵ鸵�Ѵ�.
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
		if (buttons.size() == 1 || selectFlag) {	// ó������ ����� ��ư�� Ŭ�� �� ������ ����
			select(x, y);
		}
	}
	void draw()const {
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i]->draw();
		}
		map[this->y][this->x]->draw();	// ���õ� ��ư�� �� ���� �ø��� ���� �ٽ� �ѹ� �׸���
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
	string click() {// ��ư ����� Ȱ��ȭ �ϰ� ������ ��ȯ
		if (existCheck(this->x, this->y)) {
			if (action != NULL) {
				return action(this);	// buttonManager�� action�� ��ϵǾ��ִٸ� �̸� �켱���� ����
			}
			else {
				return map[this->y][this->x]->click();	// buttonManager�� action�� ���ٸ� button�� action�� ����
			}
		}
	}
	string getSelectedButtonText() {	// ���� ���õ� ��ư�� �ؽ�Ʈ ��ȯ
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