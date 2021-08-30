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

	//Parent
	UIElement* parent = NULL;


	//Self
	int x, y, w, h;	// 요소의 좌표와 크기
	bool endFlag = false;	// UI 동작이 끝난는지 여부
	string name; // 요소의 이름
	bool borderFlag = true;	// 테두리 출력 여부
	bool terminalFlag = true; // 말단 노드 여부
	bool pointableSubElementEnrollFlag = false;	// 선택가능한 자식이 한 번이라도등록되었는가?
	bool statePropagationFlag = true; // state생성 시 하위 요소의 state를 포함할지 여부
	/*
		true: state생성 시 자기 자신을 포함한 하위 요소의 모든 state를 생성
		false: state생성 시 자기 자신만의 state만 생성
	*/
	bool selectPropagationFlag = true; // select 시 하위 요소로 전달할지 여부
	/* - false -> 반드시 자기 자신이 선택됨
	*  - true  -> 자식이 있다면 넘기고 없다면 자기 자신이 선택됨
	*/
	bool selectedFlag;// UIManager에 의해 선택되어있는지 여부(중요하지 않은듯...)
	Printer* unselectedPrinter = NULL, * selectedPrinter = NULL, * printer = NULL;
	Painter* unselectedPainter = NULL, * selectedPainter = NULL, * painter = NULL;

	

	//Children: 하위 요소를 map형식으로 관리
	int mapW, mapH;	// map의 크기
	vector<vector<pair<UIElement*, bool>>> map;	// 하위 요소 map <요소, 선택가능 여부>
	vector<UIElement*> children;	// 하위요소 리스트 (map에 속하는 모든 요소를 보관한다.)
	int selectPointX, selectPointY;	// 선택되는 요소의 map에서의 좌표
	/* - 하위 요소가 하나라도 있다면 유효한 값을 갖는다.
	*/


	void setSelectedState() {
		selectedFlag = true;
		printer = selectedPrinter;
		painter = selectedPainter;
	}
	void setUnselectedState() {
		selectedFlag = false;
		printer = unselectedPrinter;
		painter = unselectedPainter;
	}\

	bool checkSubElementPosRange(int x, int y) { return 0 <= x && x < mapW && 0 <= y && y < mapH; }
	bool checkSubElementExist(int x, int y) {
		return checkSubElementPosRange(x, y) && (map[y][x].first != NULL);
	}
	bool checkSubElementPointable(int x, int y) {
		return checkSubElementExist(x, y) && (map[y][x].second);
	}
	bool checkSubElementsIsEmpty() {
		return children.size() == 0;
	}

	void pointOtherSubElement(int x, int y) {
		if (!checkSubElementExist(x, y)) {
			errorPrint("no exist");
		}
		else {
			this->selectPointX = x;
			this->selectPointY = y;
		}
	}
	void selectOtherSubElement(int x, int y, bool redraw = true) {	// 다른 자식 요소를 선택한다.
		if (!checkSubElementExist(x, y)) {
			errorPrint("no exist");
		}
		else {
			unselect(redraw);
			pointOtherSubElement(x, y);
			select(redraw);
		}
	}
	UIElement* getPointedSubElement() {
		if (checkSubElementsIsEmpty())// 자식이 있는 경우만 호출되어야 한다.
			errorPrint("no child"); 

		// 자식이 존재하면 반드시 유효한 자식이 있다.
		return map[selectPointY][selectPointX].first; // 선택되어있는 자식 반환
	}	 
	int getSubElementNum() {
		return children.size();
	}
	void drawBorder() {
		if (borderFlag)	painter->rectBorder(x, y, w, h, CURSOR_STD);
	}
	void drawText() {
		vector<string>tokens = split(name, "\n");
		printer->printText(x + painter->getWidth(), y + painter->getHeight(), w - 2 * painter->getWidth(), h - 2 * painter->getHeight(), tokens);
	}


	bool selectUpChild(bool redraw = true) {	// 위에 놓인 하위 요소 선택을 수행한 후 성공 여부 반환
		if (checkSubElementPointable(selectPointX, selectPointY - 1)) {
			selectOtherSubElement(selectPointX, selectPointY - 1, redraw);
			return true;
		}
		return false;
	}
	bool selectDownChild(bool redraw = true) {
		if (checkSubElementPointable(selectPointX, selectPointY + 1)) {
			selectOtherSubElement(selectPointX, selectPointY + 1, redraw);
			return true;
		}
		cout << checkSubElementPosRange(selectPointX, selectPointY + 1) << endl;
		cout << checkSubElementExist(selectPointX, selectPointY + 1) << endl;
		return false;
	}
	bool selectRightChild(bool redraw = true) {
		if (checkSubElementPointable(selectPointX + 1, selectPointY)) {
			selectOtherSubElement(selectPointX + 1, selectPointY, redraw);
			return true;
		}
		return false;
	}
	bool selectLeftChild(bool redraw = true) {
		if (checkSubElementPointable(selectPointX - 1, selectPointY)) {
			selectOtherSubElement(selectPointX - 1, selectPointY, redraw);
			return true;
		}
		return false;
	}
	virtual void select(bool redraw = true) {	// (명목상)최하위 요소를 선택한다.
		if (selectPropagationFlag) {
			if (checkSubElementsIsEmpty()) {
				setSelectedState();
			}
			else {
				getPointedSubElement()->select(false);	// 어짜피 함수 끝에서 다시그릴 것이기 때문에 각각의 요소가 다시 그려질 필요 없음
			}
		}
		else {
			setSelectedState();
			for (auto child : children) {	// 명목상 terminal이기 때문에 이후의 하위 요소는 모두 부모를 따른다.
				child->select(false);
			}
		}
		if (redraw)draw();
	}
	virtual void unselect(bool redraw = true) {// (명목상)최하위 요소를 선택 취소한다.
		if (selectPropagationFlag) {
			if (checkSubElementsIsEmpty()) {
				setUnselectedState();
			}
			else {
				getPointedSubElement()->unselect(false);	// 어짜피 함수 끝에서 다시그릴 것이기 때문에 각각의 요소가 다시 그려질 필요 없음
			}
		}
		else {
			setUnselectedState();
			for (auto child : children) {	// 명목상 terminal이기 때문에 이후의 하위 요소는 모두 부모를 따른다.
				child->unselect(false);
			}
		}
		if (redraw)draw();
	}
	
	State(*customizedGetState)(UIElement& element) = NULL;	// 사용자 정의 getState()
	// tool
	void combineState(State& s1, const State& s2) {	// s2를 s1에 합쳐준다.
		try {
			for (auto s : s2) {
				s1[s.first] = s.second;
			}
		}catch(...) {
			errorPrint("maybe same key alread exist!");
		}
	}
public:
	UIElement(int x, int y, int w, int h, string text) :
		UIElement(x, y, w, h, text, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true, 0, 0) {};
	UIElement(int x, int y, int w, int h, string text, int mapW, int mapY) :
		UIElement(x, y, w, h, text, DEFAULT_SELECTED_PAINTER, DEFAULT_UNSELECTED_PAINTER, DEFAULT_SELECTED_PRINTER, DEFAULT_UNSELECTED_PRINTER, true, mapW, mapY) {};
	UIElement(int x, int y, int w, int h, string text, Painter* selectedPainter, Painter* unselectedPainter, Printer* selectedPrinter, Printer* unselectedPrinter, bool borderFlag, int mapW, int mapH) :
		x(x), y(y), w(w), h(h), name(text),
		selectedPainter(selectedPainter), unselectedPainter(unselectedPainter),
		selectedPrinter(selectedPrinter), unselectedPrinter(unselectedPrinter),
		borderFlag(borderFlag), mapW(mapW), mapH(mapH) {
		map = vector<vector<pair<UIElement*, bool>>>(mapH, vector<pair<UIElement*, bool>>(mapW, pair<UIElement*, bool>(NULL, false)));
		unselect(false);

	};


	// setter
	void setParent(UIElement* parent) { this->parent = parent; }
	void setBorderFlag(bool borderFlag) {
		this->borderFlag = borderFlag;
	}
	void setTerminalFlag(bool terminalFlag) { this->terminalFlag = terminalFlag; }
	void setRootEndFlag(bool endFlag) {	// root의 endFlag를 인자 값으로 변경// 종료를 위해 사용
		if (parent != NULL) {
			parent->setRootEndFlag(endFlag);
		}
		else {
			this->endFlag = endFlag;
		}
	}
	void setSelectPropagationFlag(bool flag) {
		this->selectPropagationFlag = flag;
	}
	void setStatepropagationFlag(bool flag) {
		this->statePropagationFlag = flag;
	}

	//getter
	string getName() { return name; }
	int getWidth() { return w; }
	int getHeight() { return h; }
	UIElement* getSelectedSubElement() {	// element에서 최종적으로 선택되어있는 말단 자식노드 반환
		if (selectPropagationFlag) {	//전파 여부에 따라
			if (!checkSubElementsIsEmpty()) {	// 자식이 있다면 전파
				return getPointedSubElement()->getSelectedSubElement();
			}else{ // 자식이 없다면 자기 자신이다.
				return this;
			}
		}
		else {	// 전파하지 않는다면 자기 자신이다.
			return this;
		}
	}
	virtual State getWholeState() {	// 자기 자신과 자신에게 속한 모든 하위 요소의 state를 종합하여 반환
		State state = getState();	// 자신의 state생성
		if (statePropagationFlag) {	// 전파 여부에 따라 하위 요소 state 추가
			State childState = getSubElementState();
			combineState(state, childState);
		}
		return state;
	}
	virtual State getState() {	// 자신의 state를 반환
		if (customizedGetState != NULL) {	// 사용자 정의 함수 우선
			return customizedGetState(*this);
		}
		else {
			State state;
			if (name != "") {	// 이름이 없다면 state를 만들지 않음
				state[name] = "";
			}
			return state;

		}
	}
	virtual State getSubElementState() {
		State state;
		for (int i = 0; i < children.size(); i++) {	// 모든 하위 요소의 state를 담는다.
			State childState = children[i]->getWholeState();
			combineState(state, childState);
		}
		return state;
	}
	bool checkEnd() { return endFlag; }


	virtual void enroll(UIElement* element, int x, int y, bool selectable = true, bool selectFlag = false) {
		// 등록 불가능 예외 처리
		if (!checkSubElementPosRange(x, y) || checkSubElementExist(x, y)) {
			char errorBuffer[100];
			sprintf(errorBuffer, "can not enroll button in (%d, %d)", x, y);
			errorPrint(errorBuffer);
		}

		// 자식 등록  
		element->setParent(this);	// 자식 노드에 자신을 부모로 등록한다.
		children.push_back(element);	// 자식 노드 등록
		element->move(this->x, this->y, false);	// 부모의 좌표를 기준으로 위치 재조정
		map[y][x] = make_pair(element, selectable);

		if (pointableSubElementEnrollFlag == false && selectable) {	// 처음으로 등록된 경우
			pointableSubElementEnrollFlag = true;
			pointOtherSubElement(x, y);
			select(false);
		}
		else if (selectFlag) {
			selectOtherSubElement(x, y, false);
		}
		else {
			element->unselect(false);
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


	// plot
	virtual void draw() {
		for (int i = 0; i < children.size(); i++) {
			children[i]->draw();
		}
		drawBorder();
		drawText();

	};
	virtual void redraw() {
		erase();
		draw();
	}
	void drawAllText() {//All은 자식을 모두 포함
		for (int i = 0; i < children.size(); i++) {
			children[i]->drawAllText();
		}
		drawText();
		if (!terminalFlag) {
			if (getPointedSubElement() != NULL) {
				getPointedSubElement()->draw();
			}
		}
	}
	virtual void erase() {
		Painter::GetEraser(w, h).point(x, y);	// 객체의 크기와 같은 공백의 점을 다루는 Painter로 해당 위치에 점을 찍는다.
		//Painter({ " " }).rect(x, y, w, h);
	};	// 기존 위치에 객체를 지운다.


	//handler
	virtual bool keyInputHandler(char key) {
		/*	key 입력에 대해 handling(처리)한 뒤 성공 여부 반환
			자식 -> 자신 -> 부모 순으로 성공할 때 까지 재귀로 이어진다.
		*/
		if (selectPropagationFlag) {	// 하위요소로 전달
			if (!checkSubElementsIsEmpty()) {
				UIElement* selectedChild = getPointedSubElement();	// 선택된 자식을 찾는다.
				if (selectedChild->keyInputHandler(key)) { // 선택된 자식 노드가 존재하며 핸들링에 성공하면 true반환
					return true;
				}
			}
		}
		switch ((Key)key) {
		case KEY_UP:    if (selectUpChild())		return true; break;	// key에 해당하는 handling 후 성공 시 true반환
		case KEY_DOWN:  if (selectDownChild())	return true; break;
		case KEY_LEFT:  if (selectLeftChild())	return true; break;
		case KEY_RIGHT: if (selectRightChild())	return true; break;
		case KEY_SPACE: setRootEndFlag(true); return true; break;
			return false; // 부모가 반환값을 체크하고 직접 핸들링 한다.
		}
	}
};