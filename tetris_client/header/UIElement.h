#pragma once
#include <string>
#include "UIManager.h"
#include "ColorPainter.h"
#include "ColorPrinter.h"
#include "KeyInput.h"
#define DEFAULT_SELECTED_PAINTER new ColorPainter({"*"}, AQUA, BLACK)
#define DEFAULT_UNSELECTED_PAINTER new ColorPainter({"*"}, WHITE, BLACK)
#define DEFAULT_SELECTED_PRINTER new ColorPrinter(CENTER, MIDDLE, AQUA, BLACK)
#define DEFAULT_UNSELECTED_PRINTER new ColorPrinter(CENTER, MIDDLE, WHITE, BLACK)

/*
- �ܼ�â�� ��µǴ� �߻�ü�̴�.
- ��� ��ġ�� ũ�� �Ӽ��� ���´�.
- ��°� �����, ������Ʈ ���� �޼ҵ带 ���´�.
- ���¸� ��ȭ��Ű�� ��� �Լ��� redraw�Ű������� ���� ����� ���ÿ� ������� �� �ִ�.
*/
class UIElement {

protected:
	int x, y, w, h;
	string text;
	bool borderFlag;
	Printer* unselectedPrinter = NULL, * selectedPrinter = NULL, * printer = NULL;
	Painter* unselectedPainter = NULL, * selectedPainter = NULL, * painter = NULL;

	UIElement* parent = NULL;
	int selectX, selectY, mapW, mapH;
	vector<vector<UIElement*>> map;	// ��� UIElement�� ���������� UIElement  �ڽĵ��� matrix ���·� ���Ѵ�.
	vector<UIElement*> children;


	bool rangeCheck(int x, int y) { return 0 <= x && x < mapW && 0 <= y && y < mapH; }
	bool existCheck(int x, int y) { return map[y][x] != NULL; }
	bool selectChild(int selectX, int selectY, bool redraw = true) {
		if (rangeCheck(selectX, selectY) && existCheck(selectX, selectY)) {
			if (existCheck(this->selectX, this->selectY)) {
				map[this->selectY][this->selectX]->unselect(redraw);
			}
			this->selectX = selectX;
			this->selectY = selectY;
			map[this->selectY][this->selectX]->select(redraw);
			return true;
		}
		return false;
	}
	UIElement* getSelectedChild() {
		if (rangeCheck(selectX, selectY) && existCheck(selectX, selectY))
			return map[selectY][selectX];
		else
			return NULL;
	}
	int getChildrenNum() {
		return children.size();
	}
	void drawBorder() {
		if (borderFlag)	painter->rectBorder(x, y, w, h, CURSOR_STD);
	}
	void drawText() {
		vector<string>tokens = split(text, "\n");
		printer->printText(x + painter->getWidth(), y + painter->getHeight(), w - 2 * painter->getWidth(), h - 2 * painter->getHeight(), tokens);
	}
	bool selectFlag;// UIManager�� ���� ���õǾ��ִ��� ����
public:
	UIElement(int x, int y, int w, int h, string text) :
		UIElement(x, y, w, h, text, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true, 0, 0) {};

	UIElement(int x, int y, int w, int h, string text, int mapW, int mapY) :
		UIElement(x, y, w, h, text, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true, mapW, mapY) {};

	UIElement(int x, int y, int w, int h, string text, 
		Painter* selectedPainter, Painter* unselectedPainter, 
		Printer* selectedPrinter, Printer* unselectedPrinter,
		bool borderFlag, int mapW, int mapH) :
		x(x), y(y), w(w), h(h), text(text), 
		selectedPainter(selectedPainter), unselectedPainter(unselectedPainter),
		selectedPrinter(selectedPrinter), unselectedPrinter(unselectedPrinter),
		borderFlag(borderFlag), mapW(mapW), mapH(mapH) {
		map = vector<vector<UIElement*>>(mapH, vector<UIElement*>(mapW, NULL));
		unselect(false);
	};



	int getWidth() {
		return w;
	}
	int getHeight() {
		return h;
	}
	void setParent(UIElement* parent) {
		this->parent = parent;
	}
	void enroll(UIElement* element, int x, int y, bool selectFlag = false) {
		if (!rangeCheck(x, y) || existCheck(x, y)) {
			char errorBuffer[100];
			sprintf(errorBuffer, "can not enroll button in (%d, %d)", x, y);
			errorPrint(errorBuffer);
		}
		element->setParent(this);	// �ڽ� ��忡 �ڽ��� �θ� ����Ѵ�.
		children.push_back(element);	// �ڽ� ��� ���
		element->move(this->x, this->y, false);	// �θ��� ��ǥ�� �������� ��ġ ������
		map[y][x] = element;
		unselect(false);
		if (children.size() == 1 || selectFlag) {	// ó������ ����� ��ư�� Ŭ�� �� ������ ����
			selectChild(x, y, false);
		}
		if (selectFlag) {
			selectChild(x, y, false);
		}
	}


	void selectUpChild(bool redraw = true) {
		if (!selectChild(selectX, selectY - 1, redraw)){
			if (parent != NULL) parent->selectUpChild();
		}
	}   // ���� ���� ���� �ڽ� ���� �ִ� �ڽ��� �����Ѵ�. ���� ��Ҵٸ� �θ𷹺����� up�� �����Ѵ�.
	void selectDownChild(bool redraw = true) {
		if (!selectChild(selectX, selectY + 1, redraw)) {
			if (parent != NULL) parent->selectDownChild();
		}
	}
	void selectRightChild(bool redraw = true) {
		if (!selectChild(selectX+1, selectY, redraw)) {
			if(parent != NULL)	parent->selectRightChild();
		}
	}
	void selectLeftChild(bool redraw = true) {
		if (!selectChild(selectX-1, selectY, redraw)) {
			if (parent != NULL) parent->selectLeftChild();
		}
	}


	virtual void move(int dx, int dy, bool redraw = true) {
		if (redraw)erase();
		this->x += dx;
		this->y += dy;
		for (int i = 0; i < children.size(); i++) {
			children[i]->move(dx, dy, redraw);
		}
		if (redraw) draw();
	}
	virtual void moveTo(int x, int y, bool redraw = true) {	// ��ü�� (x, y)�� �̵�
		move(x - this->x, y - this->y, redraw);
	}
	virtual void draw() {
		for (int i = 0; i < children.size(); i++) {
			children[i]->draw();
		}
		drawBorder();
		drawText();
	};
	virtual void erase() {
		for (int i = 0; i < children.size(); i++) {
			children[i]->erase();
		}
		Painter::GetEraser(w, h).point(x, y);	// ��ü�� ũ��� ���� ������ ���� �ٷ�� Painter�� �ش� ��ġ�� ���� ��´�.
	};	// ���� ��ġ�� ��ü�� �����.
	virtual void select(bool redraw = true) {
		if (getChildrenNum() > 0)
			return;	// �ڽ��� ������ �ڽ��� ���õ� �� ����. -> ������ ���� ��忡�� �̷������.
		selectFlag = true;
		printer = selectedPrinter;
		painter = selectedPainter;
		if (redraw)draw();
	}
	virtual void unselect(bool redraw = true){
		selectFlag = false;
		printer = unselectedPrinter;
		painter = unselectedPainter;
		if(redraw)draw();
	}
	virtual void keyInputHandler(char key) {	// Ư�� Ű�� ���� um�� � ������ �Ͼ �� ���� ����
		UIElement* selectedChild = getSelectedChild();
		if (selectedChild == NULL) {
			switch ((Key)key) {
			case KEY_UP:    selectUpChild();    break;
			case KEY_DOWN:  selectDownChild();  break;
			case KEY_LEFT:  selectLeftChild();  break;
			case KEY_RIGHT: selectRightChild(); break;
			}
		}
		else {
			selectedChild->keyInputHandler(key);
		}
	}
};