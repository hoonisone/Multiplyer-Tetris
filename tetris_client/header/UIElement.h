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
- 콘솔창에 출력되는 추상객체이다.
- 출력 위치와 크기 속성을 갖는다.
- 출력과 지우기, 업데이트 등의 메소드를 갖는다.
- 상태를 변화시키는 모든 함수는 redraw매개변수를 통해 변경과 동시에 재출력할 수 있다.
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
	vector<vector<UIElement*>> map;	// 모든 UIElement는 내부적으로 UIElement  자식들을 matrix 형태로 지닌다.
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
	bool selectFlag;// UIManager에 의해 선택되어있는지 여부
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
		element->setParent(this);	// 자식 노드에 자신을 부모를 등록한다.
		children.push_back(element);	// 자식 노드 등록
		element->move(this->x, this->y, false);	// 부모의 좌표를 기준으로 위치 재조정
		map[y][x] = element;
		unselect(false);
		if (children.size() == 1 || selectFlag) {	// 처음으로 등록한 버튼이 클린 된 것으로 간주
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
	}   // 현재 선택 중인 자식 위에 있는 자식을 선택한다. 벽에 닿았다면 부모레벨에서 up을 수행한다.
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
	virtual void moveTo(int x, int y, bool redraw = true) {	// 객체를 (x, y)로 이동
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
		Painter::GetEraser(w, h).point(x, y);	// 객체의 크기와 같은 공백의 점을 다루는 Painter로 해당 위치에 점을 찍는다.
	};	// 기존 위치에 객체를 지운다.
	virtual void select(bool redraw = true) {
		if (getChildrenNum() > 0)
			return;	// 자식이 있으면 자신은 선택될 수 없다. -> 선택은 말단 노드에서 이루어진다.
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
	virtual void keyInputHandler(char key) {	// 특정 키에 대해 um에 어떤 동작이 일어날 지 결정 가능
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