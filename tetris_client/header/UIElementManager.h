#pragma once
#include "UIElement.h"
#include "error.h"
#include "string+.h"
#include <vector>
#pragma warning(disable : 4996)

using namespace std;
/*
Ű �Է��� �޾� ��ư�� ���� ���� ��Ų��.
����Ű�� ��ư �̵�(����)
�����̽��� ��ư Ŭ��(���õ� ��ư ������ ��ȯ�Ѵ�.)
������ Ű�� ��ư���� �Ѱ� �ڵ鸵�Ѵ�.
*/
class UIElementManager{
private:
	int width, height;
	int x = 0, y = 0;
	vector<vector<UIElement*>> map;
	vector<UIElement*> buttons;
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
	string (*action)(UIElementManager* button) = NULL;
public:
	vector<UIElement*> getButtons() {
		return buttons;
	}
	UIElementManager(int width, int height):width(width), height(height) {
		map = vector<vector<UIElement*>>(height, vector<UIElement*>(width, NULL));
	}

	void enroll(UIElement* element, int x, int y, bool selectFlag = false) {
		if (!rangeCheck(x, y) || existCheck(x, y)) {
			char errorBuffer[100];
			sprintf(errorBuffer, "can not enroll button in (%d, %d)", x, y);
			errorPrint(errorBuffer);
		}
		buttons.push_back(element);
		map[y][x] = element;
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
	void setAction(string (*action)(UIElementManager* button)) {
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
	vector<pair<string, string>> getState() {// buttonManager�� ���¸� ��ȯ�Ѵ�. scanner Button�鿡 ���� key value�� ��ȯ���ش�.

	}
	~UIElementManager() {
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