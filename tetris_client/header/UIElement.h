#pragma once
#include <string>
#include "ColorPainter.h"
#include "ColorPrinter.h"
#include "KeyInput.h"
#include <unordered_map>
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
using State = unordered_map<string, string>;
class UIElement {
protected:
	int x, y, w, h;
	string name;
	bool borderFlag = true;
	bool terminalFlag = true; // ���� ������� ���θ� ��Ÿ���� true�� ��쿡�� selected�� �ڽ����� �̺�Ʈ ������ ����
	Printer* unselectedPrinter = NULL, * selectedPrinter = NULL, * printer = NULL;
	Painter* unselectedPainter = NULL, * selectedPainter = NULL, * painter = NULL;

	UIElement* parent = NULL;
	int selectX, selectY, mapW, mapH;
	vector<vector<pair<UIElement*, bool>>> map;	// ��� UIElement�� ���������� UIElement  �ڽĵ��� matrix ���·� ���Ѵ�.	second�� ���� ���� ����
	vector<UIElement*> children;
	bool endFlag = false;

	bool rangeCheck(int x, int y) { return 0 <= x && x < mapW && 0 <= y && y < mapH; }
	bool existCheck(int x, int y) { return map[y][x].second; }
	bool selectChild(int selectX, int selectY, bool redraw = true) {
		if (rangeCheck(selectX, selectY) && existCheck(selectX, selectY)) {
			if (existCheck(this->selectX, this->selectY)) {
				map[this->selectY][this->selectX].first->unselect(redraw);
			}
			this->selectX = selectX;
			this->selectY = selectY;
			map[this->selectY][this->selectX].first->select(redraw);
			return true;
		}
		return false;
	}
	UIElement* getSelectedChild() {
		if (rangeCheck(selectX, selectY) && existCheck(selectX, selectY))
			return map[selectY][selectX].first;
		else
			return NULL;
	}	 // ���õǾ��ִ� �ڽ� ��ȯ
	int getChildrenNum() {
		return children.size();
	}
	void drawBorder() {
		if (borderFlag)	painter->rectBorder(x, y, w, h, CURSOR_STD);
	}
	void drawText() {
		vector<string>tokens = split(name, "\n");
		printer->printText(x + painter->getWidth(), y + painter->getHeight(), w - 2 * painter->getWidth(), h - 2 * painter->getHeight(), tokens);
	}
	
	bool selectFlag;// UIManager�� ���� ���õǾ��ִ��� ����
	bool selectUpChild(bool redraw = true) {
		return selectChild(selectX, selectY - 1, redraw);
	}
	bool selectDownChild(bool redraw = true) {
		return selectChild(selectX, selectY + 1, redraw);
	}
	bool selectRightChild(bool redraw = true) {
		return selectChild(selectX + 1, selectY, redraw);
	}
	bool selectLeftChild(bool redraw = true) {
		return selectChild(selectX - 1, selectY, redraw);
	}
	virtual void select(bool redraw = true) {
		if (!terminalFlag)
			return;	// �ڽ��� ������ �ڽ��� ���õ� �� ����. -> ������ ���� ��忡�� �̷������.
		selectFlag = true;
		printer = selectedPrinter;
		painter = selectedPainter;
		for (auto child : children) {
			child->select(redraw);
		}
		if (redraw)draw();
	}
	virtual void unselect(bool redraw = true) {
		selectFlag = false;
		printer = unselectedPrinter;
		painter = unselectedPainter;
		if (terminalFlag) {
			for (auto child : children) {
				child->unselect(redraw);
			}
		}
		
		if (redraw)draw();
	}

public:
	UIElement(int x, int y, int w, int h, string text) :
		UIElement(x, y, w, h, text, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true, 0, 0) {};
	UIElement(int x, int y, int w, int h, string text, int mapW, int mapY) :
		UIElement(x, y, w, h, text, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true, mapW, mapY) {};
	UIElement(int x, int y, int w, int h, string text, 
		Painter* selectedPainter, Painter* unselectedPainter, 
		Printer* selectedPrinter, Printer* unselectedPrinter,
		bool borderFlag, int mapW, int mapH) :
		x(x), y(y), w(w), h(h), name(text), 
		selectedPainter(selectedPainter), unselectedPainter(unselectedPainter),
		selectedPrinter(selectedPrinter), unselectedPrinter(unselectedPrinter),
		borderFlag(borderFlag), mapW(mapW), mapH(mapH) {
		map = vector<vector<pair<UIElement*, bool>>>(mapH, vector<pair<UIElement*, bool>>(mapW, pair<UIElement*, bool>(NULL, false)));
		unselect(false);
	};
	void setBorderFlag(bool borderFlag) {
		this->borderFlag = borderFlag;
	}
	int getWidth() {
		return w;
	}
	int getHeight() {
		return h;
	}
	void setParent(UIElement* parent) {
		this->parent = parent;
	}
	virtual void enroll(UIElement* element, int x, int y, bool selectable = true, bool selectFlag = false) {
		// ��� �Ұ��� ���� ó��
		if (!rangeCheck(x, y) || existCheck(x, y)) {	
			char errorBuffer[100];
			sprintf(errorBuffer, "can not enroll button in (%d, %d)", x, y);
			errorPrint(errorBuffer);
		}

		// �ڽ� ���
		element->setParent(this);	// �ڽ� ��忡 �ڽ��� �θ�� ����Ѵ�.
		children.push_back(element);	// �ڽ� ��� ���
		element->move(this->x, this->y, false);	// �θ��� ��ǥ�� �������� ��ġ ������
		map[y][x] = make_pair(element, selectable);

		if (terminalFlag) {
			if(selectFlag)
				element->select(false);	// ���õ� ����� �ڽ��� ��� ���� ó��
		}else{
			if (children.size() == 1 || selectFlag) {	// ó������ ��ϵǰų� �ܺο��� ������ ��� select ó��
				unselect(false);	// �ڽ��� �ִ� ���� select�� �� ���⿡  select�� ���
				selectChild(x, y, false);
			}
		}
	}
	void setTerminalFlag(bool terminalFlag) {
		this->terminalFlag = terminalFlag;
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
		if (!terminalFlag) {
			if (getSelectedChild() != NULL) {
				getSelectedChild()->draw();
			}
		}
	};
	void drawAllText() {//All�� �ڽ��� ��� ����
		for (int i = 0; i < children.size(); i++) {
			children[i]->drawAllText();
		}
		drawText();
		if (!terminalFlag) {
			if (getSelectedChild() != NULL) {
				getSelectedChild()->draw();
			}
		}
	}
	virtual void erase() {
		Painter::GetEraser(w, h).point(x, y);	// ��ü�� ũ��� ���� ������ ���� �ٷ�� Painter�� �ش� ��ġ�� ���� ��´�.
		//Painter({ " " }).rect(x, y, w, h);
	};	// ���� ��ġ�� ��ü�� �����.
	virtual void redraw() {
		erase();
		draw();
	}
	virtual bool keyInputHandler(char key) {
	/*	key �Է¿� ���� handling(ó��)�� �� ���� ���� ��ȯ
		�ڽ� -> �ڽ� -> �θ� ������ ������ �� ���� ��ͷ� �̾�����.
	*/
		if (terminalFlag) {
			return false;
		}
		else { // ���ܰ� �ƴ϶��
			UIElement* selectedChild = getSelectedChild();	// ���õ� �ڽ��� ã�´�.
			if (selectedChild != NULL && selectedChild->keyInputHandler(key)) { // ���õ� �ڽ� ��尡 �����ϸ� �ڵ鸵�� �����ϸ� true��ȯ
				return true;
			}
			switch ((Key)key) {
			case KEY_UP:    if (selectUpChild())		return true; break;	// key�� �ش��ϴ� handling �� ���� �� true��ȯ
			case KEY_DOWN:  if (selectDownChild())	return true; break;
			case KEY_LEFT:  if (selectLeftChild())	return true; break;
			case KEY_RIGHT: if (selectRightChild())	return true; break;
			case KEY_SPACE: setRootEndFlag(true); return true; break;
			}
		}
		
		return false; // �θ� ��ȯ���� üũ�ϰ� ���� �ڵ鸵 �Ѵ�.
	}
	bool endCheck() {
		return endFlag;
	}
	void setRootEndFlag(bool endFlag) {	// root�� endFlag�� ���� ������ ����
		if (parent != NULL) {
			parent->setRootEndFlag(endFlag);
		}
		else {
			this->endFlag = endFlag;
		}
	}
	virtual State getState() {
		State state;
		for (int i = 0; i < children.size(); i++) {
			State childState = children[i]->getState();
			for (auto i : childState) {
				state[i.first] = i.second;
			}
		}
		state[name] = "";
		return state;
	}
	UIElement* getSelectedElement() {	// element���� ���������� ���õǾ��ִ� ���� �ڽĳ�� ��ȯ
		if (terminalFlag) {	//���� �����
			return this;
		}
		else {//���� ��尡 �ƴ϶�� ���õ� �ڽĿ��� �н�
			return getSelectedChild()->getSelectedElement();
		}
	}
	string getName() {
		return name;
	}
};