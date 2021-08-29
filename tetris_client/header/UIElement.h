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
- 콘솔창에 출력되는 추상객체이다.
- 출력 위치와 크기 속성을 갖는다.
- 출력과 지우기, 업데이트 등의 메소드를 갖는다.
- 상태를 변화시키는 모든 함수는 redraw매개변수를 통해 변경과 동시에 재출력할 수 있다.
*/
using State = unordered_map<string, string>;
class UIElement {
protected:
	int x, y, w, h;
	string name;
	bool borderFlag = true;
	bool terminalFlag = true; // 말단 노드인지 여부를 나타내며 true인 경우에만 selected와 자식으로 이벤트 전달이 가능
	Printer* unselectedPrinter = NULL, * selectedPrinter = NULL, * printer = NULL;
	Painter* unselectedPainter = NULL, * selectedPainter = NULL, * painter = NULL;

	UIElement* parent = NULL;
	int selectX, selectY, mapW, mapH;
	vector<vector<pair<UIElement*, bool>>> map;	// 모든 UIElement는 내부적으로 UIElement  자식들을 matrix 형태로 지닌다.	second는 선택 가능 여부
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
	}	 // 선택되어있는 자식 반환
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
	
	bool selectFlag;// UIManager에 의해 선택되어있는지 여부
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
			return;	// 자식이 있으면 자신은 선택될 수 없다. -> 선택은 말단 노드에서 이루어진다.
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
		// 등록 불가능 예외 처리
		if (!rangeCheck(x, y) || existCheck(x, y)) {	
			char errorBuffer[100];
			sprintf(errorBuffer, "can not enroll button in (%d, %d)", x, y);
			errorPrint(errorBuffer);
		}

		// 자식 등록
		element->setParent(this);	// 자식 노드에 자신을 부모로 등록한다.
		children.push_back(element);	// 자식 노드 등록
		element->move(this->x, this->y, false);	// 부모의 좌표를 기준으로 위치 재조정
		map[y][x] = make_pair(element, selectable);

		if (terminalFlag) {
			if(selectFlag)
				element->select(false);	// 선택된 노드의 자식은 모두 선택 처리
		}else{
			if (children.size() == 1 || selectFlag) {	// 처음으로 등록되거나 외부에서 설정한 경우 select 처리
				unselect(false);	// 자식이 있는 노드는 select될 수 없기에  select를 취소
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
	virtual void moveTo(int x, int y, bool redraw = true) {	// 객체를 (x, y)로 이동
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
	void drawAllText() {//All은 자식을 모두 포함
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
		Painter::GetEraser(w, h).point(x, y);	// 객체의 크기와 같은 공백의 점을 다루는 Painter로 해당 위치에 점을 찍는다.
		//Painter({ " " }).rect(x, y, w, h);
	};	// 기존 위치에 객체를 지운다.
	virtual void redraw() {
		erase();
		draw();
	}
	virtual bool keyInputHandler(char key) {
	/*	key 입력에 대해 handling(처리)한 뒤 성공 여부 반환
		자식 -> 자신 -> 부모 순으로 성공할 때 까지 재귀로 이어진다.
	*/
		if (terminalFlag) {
			return false;
		}
		else { // 말단가 아니라면
			UIElement* selectedChild = getSelectedChild();	// 선택된 자식을 찾는다.
			if (selectedChild != NULL && selectedChild->keyInputHandler(key)) { // 선택된 자식 노드가 존재하며 핸들링에 성공하면 true반환
				return true;
			}
			switch ((Key)key) {
			case KEY_UP:    if (selectUpChild())		return true; break;	// key에 해당하는 handling 후 성공 시 true반환
			case KEY_DOWN:  if (selectDownChild())	return true; break;
			case KEY_LEFT:  if (selectLeftChild())	return true; break;
			case KEY_RIGHT: if (selectRightChild())	return true; break;
			case KEY_SPACE: setRootEndFlag(true); return true; break;
			}
		}
		
		return false; // 부모가 반환값을 체크하고 직접 핸들링 한다.
	}
	bool endCheck() {
		return endFlag;
	}
	void setRootEndFlag(bool endFlag) {	// root의 endFlag를 인자 값으로 변경
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
	UIElement* getSelectedElement() {	// element에서 최종적으로 선택되어있는 말단 자식노드 반환
		if (terminalFlag) {	//말단 노드라면
			return this;
		}
		else {//말단 노드가 아니라면 선택된 자식에게 패스
			return getSelectedChild()->getSelectedElement();
		}
	}
	string getName() {
		return name;
	}
};